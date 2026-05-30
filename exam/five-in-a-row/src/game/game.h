#ifndef game_h
#define game_h

#include "../core/board.h"
#include "../players/player.h"
#include "../players/computer.h"
#include "history.h"

// класс управляет игрой
class game {
public:
    // принимает двух игроков и стратегию
    game(player& player_x, player& player_o, const computer& strategy);
    void run();

private:
    // возвр текущее время в виде строки (эт для меток ходов)
    std::string get_current_time() const;

    board board_;
    history history_;
    player& player_x_;
    player& player_o_;
    const computer& strategy_;
    player* current_player_;
};

#endif