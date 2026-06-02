#ifndef board_h
#define board_h

#include "cell.h"
#include <vector>
#include <string>

// класс поле 20x20
// содержит матрицу ячеек и методы для работы с ними

class board {
public:
    static const int SIZE = 20;

    board();

    void display() const;
    bool is_valid(int row, int col) const;
    bool place(int row, int col, char symbol); // теперь возвращает bool
    bool check_win(int row, int col, char symbol) const;
    bool check_loop_win(int row, int col, char symbol) const;
    bool is_full() const;
    char get_symbol_at(int row, int col) const;

private:
    cell cells_[SIZE][SIZE];
};

#endif