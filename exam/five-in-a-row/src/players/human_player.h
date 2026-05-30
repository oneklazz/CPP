#ifndef human_player_h
#define human_player_h

#include "player.h"
#include "../core/board.h"
#include "../game/history.h"
#include "../players/computer_player.h"

// класс человек игрок
class human_player : public player {
public:
    explicit human_player(char symbol);
    move get_move(const board& b, int move_number) override;
    void set_context(history* h, computer_player* c);

private:
    std::string get_current_time() const;
    history* history_;
    computer_player* computer_;
};

#endif