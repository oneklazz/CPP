#pragma once
#include <vector>
#include <string>

class Figure {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;
    virtual ~Figure() {}
};

// точка
struct Dot {
    double x, y;
    Dot(double x = 0, double y = 0) : x(x), y(y) {}
};

// круг
class Round : public Figure {
    Dot center;
    double rad;
public:
    Round(const Dot& c, double r) : center(c), rad(r) {}
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// эллипс
class Oval : public Figure {
    Dot center;
    double bigRad;
    double smallRad;
public:
    Oval(const Dot& c, double br, double sr) : center(c), bigRad(br), smallRad(sr) {}
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// прямоугольник
class Rect : public Figure {
    Dot topLeft;
    Dot bottomRight;
public:
    Rect(const Dot& tl, const Dot& br); // от двух точек
    Rect(double width, double height); // от сторон
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// треугольник
class Tri : public Figure {
    Dot vertA, vertB, vertC;
public:
    Tri(const Dot& a, const Dot& b, const Dot& c); // от трех точек
    Tri(double a, double b, double c); // от трех сторон
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

// многоугольник
class Poly : public Figure {
    std::vector<Dot> points;
public:
    Poly(const std::string& file);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};