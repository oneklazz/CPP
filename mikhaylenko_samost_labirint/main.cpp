#include "labirint.h"
#include <iostream>

int main() {
    // загружаем картинку с лабиринтом
    kartinka img(1, 1);
    if (!img.zagruzit("ДНК_Лабиринт.bmp")) {
        std::cout << "не удалось открыть ДНК_Лабиринт.bmp" << std::endl;
        return 1;
    }

    std::cout << "картинка загружена, размер: " << img.get_w() << "x" << img.get_h() << std::endl;

    // создаём лабиринт
    labirint lab(img);

    // ищем путь
    std::vector<tochka> put = lab.najti_put();

    if (put.empty()) {
        std::cout << "путь не найден" << std::endl;
        return 1;
    }

    std::cout << "путь найден! шагов: " << put.size() << std::endl;

    // рисуем путь на копии картинки и сохраняем
    kartinka result = img;
    lab.narisovat_put(result, put);

    if (result.sohranit("ДНК_Лабиринт_решение.bmp")) {
        std::cout << "готово! смотрите ДНК_Лабиринт_решение.bmp" << std::endl;
    } else {
        std::cout << "ошибка сохранения" << std::endl;
    }

    return 0;
}