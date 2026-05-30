#ifndef player_h
#define player_h

#include "../core/board.h"
#include "../core/move.h"

// абстрактный класс игрок
class player {
public:
    virtual ~player() = default;
    virtual move get_move(const board& b, int move_number) = 0;
    char get_symbol() const;

protected:
    explicit player(char symbol);

private:
    char symbol_;
};

#endif