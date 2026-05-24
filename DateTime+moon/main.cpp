#include "moon.h"
#include <iostream>

using namespace std;

int main() {
    int day, month, year;
    char dot;

    cout << "введите дату (дд.мм.гггг): ";
    cin >> day >> dot >> month >> dot >> year;

    try {
        // создаём объект Moon с введённой датой
        Moon moon(day, month, year);

        if (!moon.load()) {
            cout << "ошибка: не удалось загрузить данные" << endl;
            return 1;
        }
        
        moon.printResult();

    } catch (const exception& e) {
        cout << "ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}