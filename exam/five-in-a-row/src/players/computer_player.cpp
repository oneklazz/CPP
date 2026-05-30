#include "computer_player.h"
#include "../core/move.h"

// сохр символ и ссылку на стратегию
computer_player::computer_player(char symbol, const computer& strategy)
    : player(symbol), strategy_(strategy) {}

// комп делает ход через стратегию
move computer_player::get_move(const board& b, int move_number) {
    return strategy_.get_best_move(b, get_symbol(), move_number);
}

// подсказка для человека (не меняет поле)
move computer_player::get_hint(const board& b, int move_number) const {
    return strategy_.get_hint(b, get_symbol(), move_number);
}