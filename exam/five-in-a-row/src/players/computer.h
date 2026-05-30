#ifndef computer_h
#define computer_h

#include "../core/board.h"
#include "../core/move.h"

// класс стратегия компьютера (эвристика)
class computer {
public:
    move get_best_move(const board& b, char player_symbol, int move_number) const;
    move get_hint(const board& b, char player_symbol, int move_number) const;

private:
    int evaluate_cell(const board& b, int row, int col, char player_symbol) const;
    std::string get_current_time() const;
};

#endif