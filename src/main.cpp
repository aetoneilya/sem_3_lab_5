#include <iostream>
#include "Engine.hpp"

int main()
{
    std::cout << "Game Wolfs and Rabbits:" << std::endl
              << "1 - set initial state manually" << std::endl
              << "2 - set initial state randomly" << std::endl;

    int gameMode;

    std::cin >> gameMode;
    if (gameMode != 1 && gameMode != 2)
    {
        std::cout << "Incorrect input" << std::endl;
    }

    Engine ZayacWolk(gameMode);
    ZayacWolk.startGame();
}