#include "game.h"
#include "../core/move.h"
#include "../players/computer_player.h"
#include <iostream>
#include <ctime>

// конструктор, сохр игроков и стратегию
game::game(player& player_x, player& player_o, const computer& strategy)
    : player_x_(player_x), player_o_(player_o), strategy_(strategy), current_player_(&player_x) {}

// возвр текущее время в виде строки
std::string game::get_current_time() const {
    time_t now = time(nullptr);
    char buf[80];
    struct tm* t = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
}

// обрабатывает спец команды: подсказка (0 0) и сохр истории (-1 -1)
// возвр true, если была команда, ход не нужен
bool game::try_command(int row, int col, int& move_number) {
    if (row == 0 && col == 0) {
        computer_player* comp = dynamic_cast<computer_player*>(&player_o_);
        if (comp) {
            move hint = comp->get_hint(board_, move_number);
            std::cout << "подсказка: поставьте на (" << hint.row + 1 << ", " << hint.col + 1 << ")\n";
        } else {
            std::cout << "ошибка: компьютерный игрок не найден\n";
        }
        --move_number;
        return true;
    } else if (row == -1 && col == -1) {
        std::string filename;
        std::cout << "имя файла для сохранения (без пробелов): ";
        std::cin >> filename;
        history_.save_to_file(filename);
        --move_number;
        return true;
    }
    return false;
}

void game::run() {
    std::cout << "игра крестики-нолики 5 в ряд (поле 20x20)\n";
    std::cout << "вы играете за X, компьютер за O\n";
    std::cout << "чтобы получить подсказку, введите 0 0\n";
    std::cout << "чтобы сохранить историю, введите -1 -1\n\n";

    board_.display();

    int move_number = 0;
    bool game_over = false;

    while (!game_over) {
        ++move_number;
        move current_move;

        if (current_player_ == &player_x_) {
            // человек
            int row, col;
            std::cout << "ваш ход (или 0 0 для подсказки, -1 -1 для сохранения): ";
            std::cin >> row >> col;
            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "некорректный ввод.\n";
                --move_number;
                continue;
            }

            if (try_command(row, col, move_number)) continue;

            // обычный ход
            --row; --col;
            if (!board_.is_valid(row, col)) {
                std::cout << "клетка занята или вне поля.\n";
                --move_number;
                continue;
            }
            current_move = player_x_.get_move(board_, move_number);
            board_.place(row, col, current_move.symbol);
        } else {
            // компьютер
            current_move = current_player_->get_move(board_, move_number);
            board_.place(current_move.row, current_move.col, current_move.symbol);
            std::cout << "компьютер поставил " << current_move.symbol
                      << " на (" << current_move.row + 1 << ", " << current_move.col + 1 << ")\n";
        }

        history_.add_move(current_move);

        if (board_.check_win(current_move.row, current_move.col, current_move.symbol)) {
            board_.display();
            std::cout << "игрок " << current_move.symbol << " победил!\n";
            history_.save_to_file("game_history.txt");
            game_over = true;
            break;
        }

        if (board_.is_full()) {
            board_.display();
            std::cout << "ничья! поле заполнено.\n";
            history_.save_to_file("game_history.txt");
            game_over = true;
            break;
        }

        board_.display();

        // переключаем игрока
        current_player_ = (current_player_ == &player_x_) ? &player_o_ : &player_x_;
    }
}