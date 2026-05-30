#include "cell.h"

// конструктор по умолч, пустая клетка
cell::cell() : symbol_('_') {}

// с заданным символом
cell::cell(char symbol) : symbol_(symbol) {}

// возвр символ в клетке
char cell::get_symbol() const {
    return symbol_;
}

void cell::set_symbol(char symbol) {
    symbol_ = symbol;
}

bool cell::is_empty() const {
    return symbol_ == '_';
}