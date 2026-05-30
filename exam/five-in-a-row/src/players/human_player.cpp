#include "human_player.h"
#include "../core/move.h"
#include <iostream>
#include <ctime>

// запрашивает инпут и возвращает ход
human_player::human_player(char symbol) : player(symbol) {}

move human_player::get_move(const board& b, int move_number) {
    int row, col;
    while (true) {
        std::cout << "ваш ход (строка столбец через пробел, 1-" << board::SIZE << "): ";
        std::cin >> row >> col;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "некорректный ввод. попробуйте снова.\n";
            continue;
        }
        // переводим в 0-индекс
        row--; col--;
        if (b.is_valid(row, col)) {
            std::string timestamp = get_current_time();
            return move(move_number, get_symbol(), row, col, timestamp, false);
        } else {
            std::cout << "клетка занята или вне поля. попробуйте снова.\n";
        }
    }
}

// эт чтоб в истории ходов сохранялась временная метка, то есть когда был сделан ход
std::string human_player::get_current_time() const {
    time_t now = time(nullptr);
    char buf[80];
    struct tm* t = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}