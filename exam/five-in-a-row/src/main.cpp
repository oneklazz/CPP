#include <iostream>
#include "game/game.h"
#include "players/human_player.h"
#include "players/computer_player.h"
#include "players/computer.h"

// создает все, стратегию, игроков и запускает игру
int main() {
    computer strategy;
    human_player human('X');
    computer_player computer('O', strategy);

    game game(human, computer, strategy);
    game.run();

    std::cout << "\nигра завершена, не забудьте сохранить историю, если еще не сделали.\n";
    return 0;
}