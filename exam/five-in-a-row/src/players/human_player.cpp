#include "human_player.h"
#include "../core/move.h"
#include <iostream>
#include <ctime>

// сохраняет символ, указатели пока пустые
human_player::human_player(char symbol) : player(symbol), history_(nullptr), computer_(nullptr) {}

// сохраняет историю и компьютер для команд
void human_player::set_context(history* h, computer_player* c) {
    history_ = h;
    computer_ = c;
}

// запрашивает инпут и возвр ход
move human_player::get_move(const board& b, int move_number) {
    int row, col;
    while (true) {
        std::cout << "ваш ход (строка столбец через пробел, 1-" << board::SIZE << ")\n";
        std::cout << "(или 0 0 для подсказки, -1 -1 для сохранения): ";
        std::cin >> row >> col;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "некорректный ввод. попробуйте снова.\n";
            continue;
        }

        // проверка на команды
        if (row == 0 && col == 0) {
            if (computer_) {
                move hint = computer_->get_hint(b, move_number);
                std::cout << "подсказка: поставьте на (" << hint.row + 1 << ", " << hint.col + 1 << ")\n";
            } else {
                std::cout << "ошибка: компьютерный игрок не найден\n";
            }
            continue;
        }
        if (row == -1 && col == -1) {
            if (history_) {
                std::string filename;
                std::cout << "имя файла для сохранения (без пробелов): ";
                std::cin >> filename;
                history_->save_to_file(filename);
            } else {
                std::cout << "ошибка: история не доступна\n";
            }
            continue;
        }

        // обычный ход
        row--; col--;
        if (b.is_valid(row, col)) {
            std::string timestamp = get_current_time();
            return move(move_number, get_symbol(), row, col, timestamp, false);
        } else {
            std::cout << "клетка занята или вне поля. попробуйте снова.\n";
        }
    }
}

// эт чтоб в истории ходов сохр временная метка, то есть когда был сделан ход
std::string human_player::get_current_time() const {
    time_t now = time(nullptr);
    char buf[80];
    struct tm* t = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}