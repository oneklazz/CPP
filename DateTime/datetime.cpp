#include "datetime.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

// проверяет, является ли год високосным
bool DateTime::isLeap(int y) const {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

// возвращает количество дней в месяце
int DateTime::daysInMonth(int y, int m) const {
    if (m == 2) return isLeap(y) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

// пересчитывает totalDays на основе год месяц день
void DateTime::recomputeTotalDays() {
    totalDays = 0;
    // дни за полные года от 1900
    for (int y = 1900; y < year; ++y) {
        totalDays += isLeap(y) ? 366 : 365;
    }
    // дни за полные месяцы в этом году
    for (int m = 1; m < month; ++m) {
        totalDays += daysInMonth(year, m);
    }
    // дни в этом месяце
    totalDays += day - 1;
}

// конструктор по умолчанию 1900-01-01
DateTime::DateTime() {
    year = 1900;
    month = 1;
    day = 1;
    hour = minute = second = 0;
    recomputeTotalDays();
}

// конструктор с параметрами
DateTime::DateTime(int y, int m, int d, int h, int min, int sec)
    : year(y), month(m), day(d), hour(h), minute(min), second(sec) {
    if (!isValid()) throw invalid_argument("неправильная дата");
    recomputeTotalDays();
}

// конструктор из строки yyyy-mm-dd или yyyy-mm-ddThh:mm:ss
DateTime::DateTime(const string& dateStr) {
    year = stoi(dateStr.substr(0, 4));
    month = stoi(dateStr.substr(5, 2));
    day = stoi(dateStr.substr(8, 2));
    if (dateStr.length() > 10) {
        hour = stoi(dateStr.substr(11, 2));
        minute = stoi(dateStr.substr(14, 2));
        second = stoi(dateStr.substr(17, 2));
    } else {
        hour = minute = second = 0;
    }
    if (!isValid()) throw invalid_argument("неправильная дата");
    recomputeTotalDays();
}

// проверяет, есть ли дата и время
bool DateTime::isValid() const {
    if (year < 1900) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    if (second < 0 || second > 59) return false;
    return true;
}

// високосный ли текущий год
bool DateTime::isLeap() const {
    return isLeap(year);
}

// возвращает дату в формате ггггммдд для поиска в файле
int DateTime::toYMD() const {
    return year * 10000 + month * 100 + day;
}

// возвращает дату в формате yyyy-mm-dd
string DateTime::toString() const {
    char buf[11];
    sprintf(buf, "%04d-%02d-%02d", year, month, day);
    return string(buf);
}

// возвращает путь к файлу с данными для этоого года
string DateTime::toFilename() const {
    return "moon/moon" + to_string(year) + ".dat";
}

// разница между двумя датами в днях
int DateTime::operator-(const DateTime& other) const {
    return totalDays - other.totalDays;
}

// + заданное количество дней
DateTime DateTime::operator+(int days) const {
    DateTime result = *this;
    for (int i = 0; i < days; ++i) {
        result.day++;
        if (result.day > daysInMonth(result.year, result.month)) {
            result.day = 1;
            result.month++;
            if (result.month > 12) {
                result.month = 1;
                result.year++;
            }
        }
    }
    result.recomputeTotalDays();
    return result;
}

// сравнения
bool DateTime::operator==(const DateTime& other) const {
    return totalDays == other.totalDays;
}

bool DateTime::operator<(const DateTime& other) const {
    return totalDays < other.totalDays;
}

bool DateTime::operator>(const DateTime& other) const {
    return totalDays > other.totalDays;
}

// определяет день недели, 1900-01-01 был понедельник
string DateTime::dayOfWeek() const {
    const char* days[] = {"понедельник", "вторник", "среда", "четверг", "пятница", "суббота", "воскресенье"};
    return days[totalDays % 7];
}

// ввод формат yyyy-mm-dd или yyyy-mm-ddThh:mm:ss
istream& operator>>(istream& is, DateTime& dt) {
    string input;
    is >> input;
    dt = DateTime(input);
    return is;
}

// вывод формат yyyy-mm-dd
ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.toString();
    return os;
}