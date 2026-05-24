#pragma once
#include "datetime.h"
#include <vector>
#include <string>

// структура для хранения одной записи из файла
struct Zapisi {
    double time; // время в часах от начала дня (это колонка T)
    double el; // угол места (это колонка El или H)
};

class Moon {
private:
    DateTime date;
    std::vector<Zapisi> data;

    bool loadData();
    double findSunrise() const;
    double findSunset() const;
    double findCulmination() const;
    std::string formatTime(double hours) const; // часы - чч:мм:сс

public:
    Moon(); // конструктор
    Moon(int day, int month, int year); // конструктор с датой

    bool load(); // загружает данные для текущей даты

    std::string getSunrise();
    std::string getSunset();
    std::string getCulmination();

    void printResult();
};