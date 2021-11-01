#include "Engine.hpp"

void Engine::draw()
{
    cleanField();

    std::cout << "Turn: " << turn << "/" << maxTurn << std::endl;
    for (auto animal : animals)
    {
        if (animal->getType() == AnimalType::RABBIT && animal->life)
            gameField[animal->getPos().y][animal->getPos().x]++;
        if (animal->getType() == AnimalType::WOLF && animal->life)
            gameField[animal->getPos().y][animal->getPos().x]--;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "=";
    std::cout << std::endl;

    for (int i = 0; i < gameField.size(); i++)
    {
        std::cout << "|";
        for (int j = 0; j < gameField[i].size(); j++)
        {
            if (gameField[i][j] == 0)
                std::cout << " ";
            else if (gameField[i][j] > 0)
                std::cout << gameField[i][j];
            // std::cout << 'R';
            else if (gameField[i][j] < 0)
                std::cout << gameField[i][j];
            // std::cout << 'W';
        }
        std::cout << "|" << std::endl;
    }

    for (int i = 0; i < width + 2; i++)
        std::cout << "=";
    std::cout << std::endl;
}

void Engine::cleanField()
{
    for (int i = 0; i < height; i++)
        for (int j = 0; j < width; j++)
        {
            gameField[i][j] = 0;
        }
}

void Engine::update()
{
    for (it = animals.begin(); it != animals.end();)
    {
        if ((*it)->life)
        {
            (*it)->update(animals, width, height);
            it++;
        }
        else
        {
            it = animals.erase(it);
        }
    }
}

void Engine::setState()
{
    std::cout << "Enter initial state in format: \n"
              << "width height numberOfTurn rabbitsAmount wolfesAmount" << std::endl;
    std::cin >> width >> height >> maxTurn >> rabbitCount >> wolfCount;

    std::cout << "Initialize Rabbits" << std::endl
              << "posX posY dir{0, 1, 2, 3} turn" << std::endl;
    for (int i = 0; i < rabbitCount; i++)
    {
        position startPos;
        int dir, turn;
        std::cin >> startPos.x >> startPos.y >> dir >> turn;
        animals.push_back(new Rabbit(startPos, Direction(dir), turn));
    }

    std::cout << "Initialize Wolfes" << std::endl
              << "posX posY dir{0, 1, 2, 3} turn" << std::endl;
    for (int i = 0; i < wolfCount; i++)
    {
        position startPos;
        int dir, turn;
        std::cin >> startPos.x >> startPos.y >> dir >> turn;
        animals.push_back(new Wolf(startPos, Direction(dir), turn));
    }
}

void Engine::setStateRandomly()
{
    std::ofstream out; // поток для записи
    out.open("log.txt");

    srand(time(0));

    width = rand() % 80 + 20;
    height = rand() % 20 + 10;
    maxTurn = rand() % 10 + 10;
    rabbitCount = rand() % 15 + 1;
    wolfCount = rand() % 15 + 1;

    out << "width: " << width << "\nheight: " << height
        << "\nmaxTurn: " << maxTurn << "\nrabbitCount: " << rabbitCount
        << "\nwolfCount: " << wolfCount << std::endl;

    std::cout << width << " " << height << "\n"
              << maxTurn << " " << rabbitCount << " " << wolfCount << std::endl;

    out << "\nRabbit:\n";
    for (int i = 0; i < rabbitCount; i++)
    {
        position startPos;
        int dir, turn;
        dir = rand() % 4;
        startPos.x = rand() % width;
        startPos.y = rand() % height;
        turn = rand() % 5 + 1;

        out << "\t" << i << ". pos - " << startPos.x << ":" << startPos.y << " "
            << "dir - " << dir << " turn - " << turn
            << "\t| " << startPos.x << " " << startPos.y << " " << dir << " " << turn << std::endl;

        animals.push_back(new Rabbit(startPos, Direction(dir), turn));
    }

    out << "\nWolves:\n";
    for (int i = 0; i < wolfCount; i++)
    {
        position startPos;
        int dir, turn;
        dir = rand() % 4;
        startPos.x = rand() % width;
        startPos.y = rand() % height;
        turn = rand() % 5 + 1;

        out << "\t" << i << ". pos - " << startPos.x << ":" << startPos.y << " "
            << "dir - " << dir << " turn - " << turn
            << "\t| " << startPos.x << " " << startPos.y << " " << dir << " " << turn << std::endl;

        animals.push_back(new Wolf(startPos, Direction(dir), turn));
    }
}

void Engine::startGame()
{
    draw();
    for (turn; turn <= maxTurn; turn++)
    {
        Sleep(1500);
        update();
        system("cls");
        draw();
    }
    system("pause");
}