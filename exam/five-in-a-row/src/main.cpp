#include <iostream>
#include "game/game.h"
#include "players/human_player.h"
#include "players/computer_player.h"
#include "players/computer.h"

// создает все, стратегию, игроков и запускает игру
int main() {
    std::cout << "выберите режим игры:\n";
    std::cout << "1. человек vs компьютер\n";
    std::cout << "2. компьютер vs компьютер\n";

    int choice;
    std::cin >> choice;

    computer strategy1;
    computer strategy2;

    if (choice == 1) {
        human_player human('X');
        computer_player computer('O', strategy1);
        game game(human, computer, strategy1);
        game.run();
    } else if (choice == 2) {
        computer_player compX('X', strategy1);
        computer_player compO('O', strategy2);
        game game(compX, compO, strategy1);
        game.run();
    } else {
        std::cout << "некорректный выбор, программа завершена.\n";
        return 1;
    }
    // computer strategy;
    // human_player human('X');
    // computer_player computer('O', strategy);
    //
    // game game(human, computer, strategy);
    // game.run();
    //
    std::cout << "\nигра завершена\n";
    return 0;
}