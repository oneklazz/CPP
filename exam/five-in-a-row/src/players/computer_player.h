#ifndef computer_player_h
#define computer_player_h

#include "player.h"
#include "computer.h"

// класс компьютер игрок
class computer_player : public player {
public:
    computer_player(char symbol, const computer& strategy);
    move get_move(const board& b, int move_number) override;
    move get_hint(const board& b, int move_number) const;

private:
    const computer& strategy_;
};

#endif