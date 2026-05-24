#include "bmp_io.h"
#include <fstream>
#include <iostream>

// читаем число из файла
template<typename T>
T read_le(std::ifstream& file) {
    T val = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        val |= (file.get() << (i * 8));
    }
    return val;
}

// создаём картинку
kartinka::kartinka(int w_, int h_) : w(w_), h(h_) {
    pikseli.resize(w * h);
}

// загрузка bmp
bool kartinka::zagruzit(const std::string& imya) {
    std::ifstream file(imya, std::ios::binary);
    if (!file) return false;

    // проверяем, что это bmp (первые 2 буквы BM)
    char head[2];
    file.read(head, 2);
    if (head[0] != 'B' || head[1] != 'M') return false;

    // пропускаем до ширины\высоты
    file.seekg(18);
    w = read_le<int>(file);
    h = read_le<int>(file);
    
    // пропускаем до глубины цвета
    file.seekg(28);
    short bpp = read_le<short>(file);
    if (bpp != 24) {
        std::cout << "ошибка: поддерживаются только 24-бит bmp" << std::endl;
        return false;
    }

    // пропускаем до начала пикселей
    file.seekg(54);

    // читаем все пиксели сразу
    int row_size = w * 3;
    std::vector<unsigned char> row(row_size);
    pikseli.resize(w * h);

    // bmp хранит строки снизу вверх
    for (int y = h - 1; y >= 0; --y) {
        file.read(reinterpret_cast<char*>(row.data()), row_size);
        for (int x = 0; x < w; ++x) {
            // bmp хранит цвета в порядке bgr то есть синий, зелёный и красный
            unsigned char b = row[x * 3];
            unsigned char g = row[x * 3 + 1];
            unsigned char r = row[x * 3 + 2];
            set_piksel(x, y, cvet(r, g, b));
        }
    }
    return true;
}

// сохранение bmp
bool kartinka::sohranit(const std::string& imya) const {
    std::ofstream file(imya, std::ios::binary);
    if (!file) return false;

    // пишем заголовок bmp
    file.put('B'); file.put('M');
    
    int file_size = 54 + w * h * 3;
    file.write(reinterpret_cast<const char*>(&file_size), 4);
    
    int reserved = 0;
    file.write(reinterpret_cast<const char*>(&reserved), 4);
    
    int offset = 54;
    file.write(reinterpret_cast<const char*>(&offset), 4);
    
    int dib_size = 40;
    file.write(reinterpret_cast<const char*>(&dib_size), 4);
    file.write(reinterpret_cast<const char*>(&w), 4);
    file.write(reinterpret_cast<const char*>(&h), 4);
    
    short planes = 1;
    file.write(reinterpret_cast<const char*>(&planes), 2);
    
    short bpp = 24;
    file.write(reinterpret_cast<const char*>(&bpp), 2);
    
    int comp = 0;
    file.write(reinterpret_cast<const char*>(&comp), 4);
    
    int img_size = w * h * 3;
    file.write(reinterpret_cast<const char*>(&img_size), 4);
    
    // переходим к пикселям
    file.seekp(54);

    // записываем пиксели снизу вверх
    std::vector<unsigned char> row(w * 3);
    for (int y = h - 1; y >= 0; --y) {
        for (int x = 0; x < w; ++x) {
            cvet c = get_piksel(x, y);
            row[x * 3] = c.b;     // синий
            row[x * 3 + 1] = c.g; // зелёный
            row[x * 3 + 2] = c.r; // красный
        }
        file.write(reinterpret_cast<const char*>(row.data()), w * 3);
    }
    return true;
}

// получить пиксель
cvet kartinka::get_piksel(int x, int y) const {
    return pikseli[y * w + x];
}

// установить пиксель
void kartinka::set_piksel(int x, int y, const cvet& c) {
    pikseli[y * w + x] = c;
}