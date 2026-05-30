#include "board.h"
#include <iostream>

// запускает все клетки пустыми
board::board() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cells_[i][j] = cell();
        }
    }
}

// вывод поля в консоль
void board::display() const {
    std::cout << "\n   ";
    for (int j = 0; j < SIZE; ++j) {
        if (j < 9) std::cout << " " << j + 1 << " ";
        else std::cout << j + 1 << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        if (i < 9) std::cout << " " << i + 1 << " ";
        else std::cout << i + 1 << " ";
        for (int j = 0; j < SIZE; ++j) {
            std::cout << " " << cells_[i][j].get_symbol() << " ";
        }
        std::cout << "\n";
    }
}

// проверяет, можно ли поставить символ в клетку в пределах поля и пустая
bool board::is_valid(int row, int col) const {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && cells_[row][col].is_empty();
}

// ставит символ в клетк
// возвращает true, если успешно, иначе false то бишь клетка занята или вне поля
bool board::place(int row, int col, char symbol) {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    if (!cells_[row][col].is_empty()) return false;
    cells_[row][col].set_symbol(symbol);
    return true;
}
// есть ли 5 в ряд от этой клетки для заданного символа
bool board::check_win(int row, int col, char symbol) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return false;
    if (cells_[row][col].get_symbol() != symbol) return false;

    // направления dx, dy
    const int dirs[4][2] = {{0,1}, {1,0}, {1,1}, {1,-1}};
    for (const auto& dir : dirs) {
        int count = 1;
        //  идем в одну сторону потом в обратную
        for (int step = 1; step < 5; ++step) {
            int nr = row + dir[0] * step;
            int nc = col + dir[1] * step;
            if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) break;
            if (cells_[nr][nc].get_symbol() == symbol) ++count;
            else break;
        }
        for (int step = 1; step < 5; ++step) {
            int nr = row - dir[0] * step;
            int nc = col - dir[1] * step;
            if (nr < 0 || nr >= SIZE || nc < 0 || nc >= SIZE) break;
            if (cells_[nr][nc].get_symbol() == symbol) ++count;
            else break;
        }
        if (count >= 5) return true;
    }
    return false;
}

// заполнено ли поле полностью
bool board::is_full() const {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (cells_[i][j].is_empty()) return false;
        }
    }
    return true;
}

// возвр символ в клетке (это для стратегии)
char board::get_symbol_at(int row, int col) const {
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE) return '_';
    return cells_[row][col].get_symbol();
}