#pragma once
#include <iostream>
#include <string>

class DateTime {
private:
    int year, month, day;
    int hour, minute, second;
    int totalDays; // количество дней от 1900-01-01

    bool isLeap(int y) const; // проверка на високосность
    int daysInMonth(int y, int m) const;
    void recomputeTotalDays();

public:
    DateTime();
    DateTime(int y, int m, int d, int h = 0, int min = 0, int sec = 0);
    DateTime(const std::string& dateStr); // парсит yyyy-mm-dd или yyyy-mm-ddThh:mm:ss

    bool isValid() const;
    bool isLeap() const;

    // геттеры
    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    int toYMD() const; // возвращает ГГГГММДД
    std::string toString() const; // возвращает yyyy-mm-dd
    std::string toFilename() const; // возвращает moon/moonГГГГ.dat

    // перегрузка операторов
    int operator-(const DateTime& other) const;
    DateTime operator+(int days) const;
    bool operator==(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator>(const DateTime& other) const;

    std::string dayOfWeek() const;   // возвращает название дня недели

    // ввод/вывод
    friend std::istream& operator>>(std::istream& is, DateTime& dt);
    friend std::ostream& operator<<(std::ostream& os, const DateTime& dt);
};