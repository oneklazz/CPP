#include "figures.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    // точки для построения фигур
    Dot a(3, 4);
    Dot b(5, 1);
    Dot c(6, 8);

    // массив указателей на фигуры, добавляем фигуры
    vector<Figure*> items;

    items.push_back(new Round(a, 4));
    items.push_back(new Oval(a, 5, 4));
    items.push_back(new Rect(a, b));
    items.push_back(new Tri(a, b, c));

    // демонстрация конструкторов от сторон
    items.push_back(new Rect(10, 6)); // прямоугольник 10x6
    items.push_back(new Tri(3, 4, 5)); // треугольник 3 4 5

    items.push_back(new Poly("granitsy-uchastka2.txt"));

    // вывод инфы о каждой фигуре
    for (size_t i = 0; i < items.size(); ++i) {
        items[i]->name();
        cout << "площадь: " << items[i]->calc_area() << endl;
        cout << "периметр: " << items[i]->calc_perimetr() << endl;
        cout << endl;
    }

    // освобождаем память
    for (size_t i = 0; i < items.size(); ++i) {
        delete items[i];
    }

    // вывод площади участка из файлау
    Poly area("granitsy-uchastka2.txt");
    cout << "=== площадь участка ===" << endl;
    cout << "площадь: " << area.calc_area() << endl;

    return 0;
}