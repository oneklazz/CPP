#include "player.h"

// сохраняет и возвращает символ игрока
player::player(char symbol) : symbol_(symbol) {}

char player::get_symbol() const {
    return symbol_;
}