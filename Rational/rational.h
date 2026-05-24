#pragma once
#include <iostream>

class Rational {
private:
    int num; // числ
    int den; // знамен

    void reduce(); // сокр дроби

public:
    Rational();
    Rational(int n);
    Rational(int n, int d);

    Rational operator+(const Rational& other) const;
    Rational& operator+=(const Rational& other);
    Rational operator-() const;
    Rational operator-(const Rational& other) const;
    Rational& operator-=(const Rational& other);
    Rational operator*(const Rational& other) const;
    Rational& operator*=(const Rational& other);
    Rational operator/(const Rational& other) const;

    bool operator==(const Rational& other) const;
    bool operator!=(const Rational& other) const;

    Rational& operator++(); // префиксный
    Rational operator++(int); // постфиксный

    operator int() const;
    operator double() const;

    Rational operator*(int n) const;
    friend Rational operator*(int n, const Rational& r);

    static Rational sqrt(const Rational& r);  // приближенный корень

    friend std::istream& operator>>(std::istream& in, Rational& r);
    friend std::ostream& operator<<(std::ostream& out, const Rational& r);
};