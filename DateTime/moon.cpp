#include "moon.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

Moon::Moon() : date(1900, 1, 1) {}

Moon::Moon(int day, int month, int year) : date(year, month, day) {}

// читает файл .dat и заполняет вектор data для этой даты
bool Moon::loadData() {
    data.clear();

    string filename = date.toFilename();
    ifstream file(filename);
    if (!file.is_open()) return false;

    int targetYMD = date.toYMD(); // нужная дата в формате ггггммдд

    string line;
    getline(file, line); // пропускает заголовок

    int ymd, hms;
    double t, r, el, az, fi, lg, sh, dl;

    while (getline(file, line)) {
        if (line.empty()) continue;
        istringstream iss(line);

        // пробуем прочитать 8 колонок
        if (iss >> ymd >> hms >> t >> r >> el >> az >> fi >> lg) {
        } else {
            // формат 2007-2008 YMD HMS R H Az Sh Dl
            iss.clear();
            iss.str(line);
            iss >> ymd >> hms >> r >> el >> az >> sh >> dl;
            // время в часах вычисляем из HMS
            int hh = hms / 10000;
            int mm = (hms / 100) % 100;
            int ss = hms % 100;
            t = hh + mm/60.0 + ss/3600.0;
        }

        // берём только записи за нужную дату
        if (ymd == targetYMD) {
            Zapisi z;
            z.time = t;
            z.el = el;
            data.push_back(z);
        }
    }

    file.close();
    return data.size() > 0;
}

bool Moon::load() {
    return loadData();
}

// переход угла места с отрицательного на положительный, то есть ищет восход
double Moon::findSunrise() const {
    for (size_t i = 0; i < data.size() - 1; i++) {
        if (data[i].el < 0 && data[i+1].el > 0) {
            double t1 = data[i].time;
            double t2 = data[i+1].time;
            double el1 = data[i].el;
            double el2 = data[i+1].el;
            // линейная интерполяция для точного времени
            return t1 + (0 - el1) * (t2 - t1) / (el2 - el1);
        }
    }
    return -1; // восход не найден
}

// тут с положительного на отрицательный, ищет заход
double Moon::findSunset() const {
    for (size_t i = 0; i < data.size() - 1; i++) {
        if (data[i].el > 0 && data[i+1].el < 0) {
            double t1 = data[i].time;
            double t2 = data[i+1].time;
            double el1 = data[i].el;
            double el2 = data[i+1].el;
            return t1 + (0 - el1) * (t2 - t1) / (el2 - el1);
        }
    }
    return -1; // заход не найден
}

//аксимальный угол места (кульминация)
double Moon::findCulmination() const {
    int maxIdx = 0;
    for (size_t i = 1; i < data.size(); i++) {
        if (data[i].el > data[maxIdx].el) {
            maxIdx = i;
        }
    }
    return data[maxIdx].time;
}

// переводит время из часов в строку чч:мм:сс
string Moon::formatTime(double hours) const {
    if (hours < 0) return "--:--:--";  // время не определено

    // округление до секунд для компенсации погрешностей double
    int totalSec = (int)(hours * 3600 + 0.5);
    int h = totalSec / 3600;
    int m = (totalSec % 3600) / 60;
    int s = totalSec % 60;

    char buf[9];
    sprintf(buf, "%02d:%02d:%02d", h, m, s);
    return string(buf);
}

// геттеры
string Moon::getSunrise() {
    return formatTime(findSunrise());
}

string Moon::getSunset() {
    return formatTime(findSunset());
}

string Moon::getCulmination() {
    return formatTime(findCulmination());
}

void Moon::printResult() {
    cout << "\nдата: ";
    int d = date.getDay();
    int m = date.getMonth();
    int y = date.getYear();
    if (d < 10) cout << "0";
    cout << d << ".";
    if (m < 10) cout << "0";
    cout << m << "." << y << endl;

    cout << "восход луны: " << getSunrise() << endl;
    cout << "кульминация луны: " << getCulmination() << endl;
    cout << "заход луны: " << getSunset() << endl;
}