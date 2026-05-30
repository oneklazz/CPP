#ifndef human_player_h
#define human_player_h

#include "player.h"

// класс человек игрок
class human_player : public player {
public:
    explicit human_player(char symbol);
    move get_move(const board& b, int move_number) override;

private:
    std::string get_current_time() const;
};

#endif