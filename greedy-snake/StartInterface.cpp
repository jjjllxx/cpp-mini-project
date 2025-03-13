#include "StartInterface.h"
#include "Point.h"
#include <unistd.h>

void gs::StartInterface::showSnakeAppear() const
{
    for (const gs::Point& pt : this->startSnake)
    {
        pt.showSquare();
        usleep(this->animInterval * 1000);
    }
}

void gs::StartInterface::showSnakeMove()
{
    for (int i = 0; i < 30; ++i)
    {
        const int j = (i % 8) < 4 ? 15 + (i % 8) : 21 - (i % 8);
        this->startSnake.emplace_back(i + 10, j);
        this->startSnake.back().showSquare();
        this->startSnake.front().clear();
        this->startSnake.pop_front();
        usleep(this->animInterval * 1000);
    }
}

void gs::StartInterface::showSnakeDisappear()
{
    while (this->startSnake.empty() == false || this->texts.back().getX() < 33)
    {
        if (this->startSnake.empty() == false)
        {
            this->startSnake.front().clear();
            this->startSnake.pop_front();
        }

        gs::StartInterface::clearText();
        gs::StartInterface::showText();
        usleep(this->animInterval * 1000);
    }
}

void gs::StartInterface::showText() const
{
    for (const gs::Point& pt : this->texts)
    {
        if (pt.getX() >= 0)
        {
            pt.showSquare();
        }
    }
}

void gs::StartInterface::clearText()
{
    for (gs::Point& pt : this->texts)
    {
        if (pt.getX() >= 0)
        {
            pt.clear();
        }

        pt.updatePos(pt.getX() + 1, pt.getY());
    }
}

void gs::StartInterface::showAll()
{
    gs::StartInterface::showSnakeAppear();
    gs::StartInterface::showSnakeMove();
    gs::StartInterface::showSnakeDisappear();
}