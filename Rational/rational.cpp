#include "rational.h"
#include <cmath>

using namespace std;

Rational::Rational() : num(0), den(1) {}
Rational::Rational(int n) : num(n), den(1) {}
Rational::Rational(int n, int d) : num(n), den(d) {}

// сокр дроби
void Rational::reduce() {
    if (den == 0) return;
    if (den < 0) { num = -num; den = -den; }

    int a = abs(num), b = den;
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    int gcd = a;
    if (gcd != 0) {
        num /= gcd;
        den /= gcd;
    }
}

Rational& Rational::operator+=(const Rational& other) {
    num = num * other.den + den * other.num;
    den = den * other.den;
    reduce();
    return *this;
}

Rational Rational::operator+(const Rational& other) const {
    Rational res = *this;
    res += other;
    return res;
}

Rational Rational::operator-() const {
    return Rational(-num, den);
}

Rational Rational::operator-(const Rational& other) const {
    return *this + (-other);
}

Rational& Rational::operator-=(const Rational& other) {
    return *this += (-other);
}

Rational& Rational::operator*=(const Rational& other) {
    num *= other.num;
    den *= other.den;
    reduce();
    return *this;
}

Rational Rational::operator*(const Rational& other) const {
    Rational res = *this;
    res *= other;
    return res;
}

Rational operator*(int n, const Rational& r) {
    return r * n;
}

Rational Rational::operator*(int n) const {
    return Rational(num * n, den);
}

Rational Rational::operator/(const Rational& other) const {
    Rational res(num * other.den, den * other.num);
    res.reduce();
    return res;
}

bool Rational::operator==(const Rational& other) const {
    return num == other.num && den == other.den;
}

bool Rational::operator!=(const Rational& other) const {
    return !(*this == other);
}

// префиксный ++
Rational& Rational::operator++() {
    num += den;
    return *this;
}

// постфиксный ++
Rational Rational::operator++(int) {
    Rational old = *this;
    num += den;
    return old;
}

Rational::operator int() const {
    return num / den;
}

Rational::operator double() const {
    return static_cast<double>(num) / den;
}

// приближенный квадратный корень
Rational Rational::sqrt(const Rational& r) {
    double val = static_cast<double>(r);
    double root = std::sqrt(val);
    return Rational(static_cast<int>(root * 1000), 1000);
}

istream& operator>>(istream& in, Rational& r) {
    in >> r.num >> r.den;
    return in;
}

ostream& operator<<(ostream& out, const Rational& r) {
    out << r.num << "/" << r.den;
    return out;
}