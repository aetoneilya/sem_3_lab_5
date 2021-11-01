#pragma once
#include <iostream>
#include <vector>
#include <list>

enum AnimalType
{
    RABBIT,
    WOLF
};

enum Direction
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct position
{
    int x;
    int y;
};

class Animal
{
public:
    position pos;
    AnimalType animalType;
    Direction dir;
    int hunger;
    int age;

    bool life;

    int dieAge;
    int turnRate;
    int walkDistance;


    virtual void update(std::list<Animal *> &animals, int width, int height) = 0;
    virtual void reproduce(std::list<Animal *>& animals) = 0;

    void die();
    void move();

    position getPos();
    AnimalType getType();
    Direction getDir();

    Animal(position pos_init, Direction dir_init, int tRate, AnimalType type, int maxAge, int walk)
    {
        pos = pos_init;
        animalType = type;
        dir = dir_init;
        hunger = 0;
        age = 0;
        life = true;
        dieAge = maxAge;
        turnRate = tRate;
        walkDistance = walk;
    }
};

class Rabbit : public Animal
{
private:
    const int maxAge = 5;
    const int walkDist = 1;

public:
    Rabbit(position pos, Direction dir, int tRate)
        : Animal(pos, dir, tRate, AnimalType::RABBIT, 15, 1) {}
    virtual void update(std::list<Animal *> &animals, int width, int height);
    virtual void reproduce(std::list<Animal *>& animals);
};

class Wolf : public Animal
{
private:
    int maxAge = 10;
    int walkDist = 2;

public:
    Wolf(position pos, Direction dir, int tRate)
        : Animal(pos, dir, tRate, AnimalType::WOLF, 30, 2) {}
    virtual void update(std::list<Animal *> &animals, int width, int height);
    virtual void reproduce(std::list<Animal *> &animals);
};