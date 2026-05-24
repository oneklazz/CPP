#include "rational.h"
#include <iostream>

using namespace std;

int main() {
    // тест конструкторов и операторовв
    Rational a(1, 2), b(-1, 6);
    cout << "a=" << a << " b=" << b << " a+b=" << a + b << endl;

    a *= b;
    cout << "a=" << a << " b=" << b << " a-b=" << a + (-b) << endl;

    Rational c = 3;
    cout << "b=" << b << " c=" << c << " b/c=" << b / c << endl;

    // тест ввода и !=
    Rational e(7, 8), f(5, 12);
    cout << "e=" << e << " f=" << f << " e+f=?" << endl;
    cout << "введите результат (числитель знаменатель): ";
    Rational g;
    cin >> g;
    if (e + f != g)
        cout << "неправильно! e+f=" << e + f << endl;
    else
        cout << "правильно!" << endl;

    // решение квадр уравнения
    Rational ra, rb, rc;
    cout << "\nвведите a: ";
    cin >> ra;
    cout << "введите b: ";
    cin >> rb;
    cout << "введите c: ";
    cin >> rc;

    Rational D = rb * rb - (ra * rc * 4);
    Rational sqrtD = Rational::sqrt(D);
    Rational x1 = (-rb + sqrtD) / (ra * 2);
    Rational x2 = (-rb - sqrtD) / (ra * 2);

    cout << "x1 = " << x1 << endl;
    cout << "x2 = " << x2 << endl;

    return 0;
}