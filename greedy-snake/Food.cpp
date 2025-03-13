#include "Food.h"
#include "Point.h"
#include "Snake.h"
#include "Utils.h"
#include <cstdlib>
#include <iostream>

void gs::Food::drawFood(const Snake& snake)
{
    while (true)
    {
        const gs::Point foodPt((rand() % 28) + 2, (rand() % 28) + 2);

        if (foodPt == this->bigPos || snake.isInSnake(foodPt) == true)
        {
            continue;
        }

        this->pos = foodPt;
        gs::Utils::setCursorPosition(this->pos.getX(), this->pos.getY());
        gs::Utils::setColor(13);
        std::cout << "*";

        if (++this->cnt == 5)
        {
            drawBigFood(snake);
            this->cnt = 0;
        }

        break;
    }
}

void gs::Food::drawBigFood(const Snake& snake)
{
    gs::Utils::setCursorPosition(5, 0);
    gs::Utils::setColor(11);
    std::cout << "------------------------------------------";
    this->progressBar = 42;

    while (true)
    {
        const gs::Point bigPt((rand() % 28) + 2, (rand() % 28) + 2);

        if (bigPt == this->pos || snake.isInSnake(bigPt) == true)
        {
            continue;
        }

        this->bigPos = bigPt;
        gs::Utils::setCursorPosition(this->bigPos.getX(), this->bigPos.getY());
        gs::Utils::setColor(18);
        std::cout << "■";
        
        this->hasBig     = true;
        this->isFlashing = true;

        break;
    }
}

void gs::Food::flashBigFood()
{
    gs::Utils::setCursorPosition(this->bigPos.getX(), this->bigPos.getY());
    gs::Utils::setColor(18);

    this->isFlashing == true ? std::cout << "  " : std::cout << "■";
    this->isFlashing = !this->isFlashing;

    gs::Utils::setCursorPosition(26, 0);
    gs::Utils::setColor(11);
    for (int i = 42; i >= this->progressBar; --i)
    {
        std::cout << "\b \b";
    }

    --this->progressBar;

    if (this->progressBar == 0)
    {
        gs::Utils::setCursorPosition(this->bigPos.getX(), this->bigPos.getY());
        std::cout << "  ";

        gs::Food::clearBigFood();
    }
}

void gs::Food::clearBigFood()
{
    this->bigPos.updatePos(0, 0);
    this->hasBig = false;
}

bool gs::Food::hasBigFood() const
{
    return this->hasBig;
}

int gs::Food::getProgressBar() const
{
    return this->progressBar;
}

gs::Point gs::Food::getPos() const
{
    return this->pos;
}

gs::Point gs::Food::getBigPos() const
{
    return this->bigPos;
}