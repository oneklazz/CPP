#include "figures.h"
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;

// круг
double Round::calc_area() {
    return 3.1415926535 * rad * rad;
}

double Round::calc_perimetr() {
    return 2 * 3.1415926535 * rad;
}

void Round::name() {
    cout << "круг" << endl;
}

// эллипс
double Oval::calc_area() {
    return 3.1415926535 * bigRad * smallRad;
}

double Oval::calc_perimetr() {
    return 3.1415926535 * (3 * (bigRad + smallRad) - sqrt((3 * bigRad + smallRad) * (bigRad + 3 * smallRad)));
}

void Oval::name() {
    cout << "эллипс" << endl;
}

// прямоугольник
Rect::Rect(const Dot& tl, const Dot& br) : topLeft(tl), bottomRight(br) {}

// прямоугольник от сторон, центр в начале координат
Rect::Rect(double width, double height) {
    double w2 = width / 2;
    double h2 = height / 2;
    topLeft = Dot(-w2, h2);
    bottomRight = Dot(w2, -h2);
}

double Rect::calc_area() {
    double w = bottomRight.x - topLeft.x;
    double h = topLeft.y - bottomRight.y;
    return w * h;
}

double Rect::calc_perimetr() {
    double w = bottomRight.x - topLeft.x;
    double h = topLeft.y - bottomRight.y;
    return 2 * (w + h);
}

void Rect::name() {
    cout << "прямоугольник" << endl;
}

// треугольник
Tri::Tri(const Dot& a, const Dot& b, const Dot& c) : vertA(a), vertB(b), vertC(c) {}

// треугольник от трех сторон с помощью формулы герона и координат
Tri::Tri(double a, double b, double c) {
    // проверка есть ли треугольник
    if (a + b <= c || a + c <= b || b + c <= a) {
        vertA = vertB = vertC = Dot(0, 0);
        return;
    }
    // A(0,0), B(c,0)
    vertA = Dot(0, 0);
    vertB = Dot(c, 0);
    // координаты C
    double x = (b * b + c * c - a * a) / (2 * c);
    double y = sqrt(b * b - x * x);
    vertC = Dot(x, y);
}

double Tri::calc_area() {
    return 0.5 * fabs(vertA.x * (vertB.y - vertC.y) +
                      vertB.x * (vertC.y - vertA.y) +
                      vertC.x * (vertA.y - vertB.y));
}

double Tri::calc_perimetr() {
    double ab = sqrt((vertB.x - vertA.x) * (vertB.x - vertA.x) +
                     (vertB.y - vertA.y) * (vertB.y - vertA.y));
    double bc = sqrt((vertC.x - vertB.x) * (vertC.x - vertB.x) +
                     (vertC.y - vertB.y) * (vertC.y - vertB.y));
    double ac = sqrt((vertA.x - vertC.x) * (vertA.x - vertC.x) +
                     (vertA.y - vertC.y) * (vertA.y - vertC.y));
    return ab + bc + ac;
}

void Tri::name() {
    cout << "треугольник" << endl;
}

// многоугольник
Poly::Poly(const string& file) {
    ifstream f(file);
    int n;
    f >> n;
    points.resize(n);
    for (int i = 0; i < n; i++) {
        f >> points[i].x >> points[i].y;
    }
}

double Poly::calc_area() {
    double area = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        area += points[i].x * points[j].y;
        area -= points[i].y * points[j].x;
    }
    return 0.5 * fabs(area);
}

double Poly::calc_perimetr() {
    double per = 0;
    int n = points.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        per += sqrt((points[j].x - points[i].x) * (points[j].x - points[i].x) +
                    (points[j].y - points[i].y) * (points[j].y - points[i].y));
    }
    return per;
}

void Poly::name() {
    cout << "многоугольник" << endl;
}