#include "game.h"
#include "../core/move.h"
#include "../players/computer_player.h"
#include "../players/human_player.h"
#include <iostream>
#include <ctime>

// конструктор, сохр игроков и стратегию
game::game(player& player_x, player& player_o, const computer& strategy)
    : player_x_(player_x), player_o_(player_o), strategy_(strategy), current_player_(&player_x) {
    // даем человеку доступ к истории и компьютеру
    human_player* h = dynamic_cast<human_player*>(&player_x_);
    if (h) {
        computer_player* c = dynamic_cast<computer_player*>(&player_o_);
        h->set_context(&history_, c);
    }
}

// возвр текущее время в виде строки
std::string game::get_current_time() const {
    time_t now = time(nullptr);
    char buf[80];
    struct tm* t = localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", t);
    return std::string(buf);
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
            current_move = player_x_.get_move(board_, move_number);
            board_.place(current_move.row, current_move.col, current_move.symbol);
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