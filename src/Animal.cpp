#include "Animal.hpp"

void Animal::die()
{
    life = false;
}

position Animal::getPos()
{
    return pos;
}

AnimalType Animal::getType()
{
    return animalType;
}

Direction Animal::getDir()
{
    return dir;
}

void Wolf::reproduce(std::list<Animal *> &animals)
{
    if (hunger >= 2)
    {
        hunger -= 2;
        animals.push_front(new Wolf(pos, dir, turnRate));
    }
}

void Rabbit::reproduce(std::list<Animal *> &animals)
{
    if (age == 5)
    {
        animals.push_front(new Rabbit(pos, dir, turnRate));
    }
    if (age == 10)
        animals.push_front(new Rabbit(pos, dir, turnRate));
}

void Animal::move()
{
    switch (dir)
    {
    case Direction::UP:
        pos.y += walkDistance;
        break;
    case Direction::RIGHT:
        pos.x += walkDistance;
        break;
    case Direction::DOWN:
        pos.y -= walkDistance;
        break;
    case Direction::LEFT:
        pos.x -= walkDistance;
        break;

    default:
        break;
    }
}

void Wolf::update(std::list<Animal *> &animals, int width, int height)
{

    move();

    pos.x = pos.x % width;
    pos.y = pos.y % height;

    if (pos.x < 0)
        pos.x += width;
    if (pos.y < 0)
        pos.y += height;

    if (age % turnRate == 0)
    {
        dir = Direction((dir + 1) % 4);
    }

    std::list<Animal *>::iterator animal;
    for (animal = animals.begin(); animal != animals.end(); animal++)
    {
        if (pos.x == (*animal)->pos.x && pos.y == (*animal)->pos.y &&
            (*animal)->animalType == AnimalType::RABBIT)
        {
            (*animal)->die();
            hunger++;
        }
    }

    age++;
    reproduce(animals);

    if (age == dieAge)
        die();
}

void Rabbit::update(std::list<Animal *> &animals, int width, int height)
{
    move();

    pos.x = pos.x % width;
    pos.y = pos.y % height;

    if (pos.x < 0)
        pos.x += width;
    if (pos.y < 0)
        pos.y += height;

    if (age % turnRate == 0)
    {
        dir = Direction((dir + 1) % 4);
    }

    age++;
    reproduce(animals);

    if (age == dieAge)
        die();
}
