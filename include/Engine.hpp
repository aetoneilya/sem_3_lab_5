#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <windows.h>
#include <ctime>

#include "Animal.hpp"

class Engine
{
private:
    std::vector<std::vector<int>> gameField;
    std::list<Animal *> animals;
    std::list<Animal *>::iterator it;

    int width;
    int height;
    int maxTurn;

    int turn;
    int rabbitCount;
    int wolfCount;

    void update();
    void draw();

public:
    void cleanField();

    void setState();
    void setStateRandomly();
    void startGame();
    Engine(int gameMode)
    {
        if (gameMode == 1)
            setState();

        else 
            setStateRandomly();

        std::cout << "set state passed\n";
        turn = 0;
        rabbitCount = 0;
        wolfCount = 0;
        gameField.resize(height);
        for (int i = 0; i < height; i++)
        {
            gameField[i].resize(width);
        }
        std::cout << "resize passed\n";
    }
};
