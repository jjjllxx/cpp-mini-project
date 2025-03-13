#include "Snake.h"
#include "Point.h"
#include "Utils.h"
#include <cstddef>
#include <iostream>
#include <ncurses.h>


void gs::Snake::initSnake()
{
    for (const gs::Point& pt : this->pts)
    {
        pt.showCircular();
    }
}

void gs::Snake::moveWithEat()
{
    switch (this->direction)
    {
    case gs::Direction::UP:
        this->pts.emplace_back(this->pts.back().getX(), this->pts.back().getY() - 1);
        break;
    case gs::Direction::DOWN:
        this->pts.emplace_back(this->pts.back().getX(), this->pts.back().getY() + 1);
        break;
    case gs::Direction::LEFT:
        this->pts.emplace_back(this->pts.back().getX() - 1, this->pts.back().getY());
        break;
    case gs::Direction::RIGHT:
        this->pts.emplace_back(this->pts.back().getX() + 1, this->pts.back().getY());
        break;
    default:
        break;
    }

    gs::Utils::setColor(14);
    this->pts.back().showCircular();
}

void gs::Snake::moveWithoutEat()
{
    moveWithEat();
    this->pts.front().clear();
    this->pts.pop_front();
}

bool gs::Snake::isInSnake(const gs::Point& pt) const
{
    for (const gs::Point& snakePt: this->pts)
    {
        if (snakePt == pt)
        {
            return true;
        }
    }

    return false;
}

bool gs::Snake::isOverEdge() const
{
    return this->pts.back().getX() >= 30 || this->pts.back().getY() >= 30 || this->pts.back().getX() <= 1 || this->pts.back().getY() <= 1;
}

bool gs::Snake::hasHitItself() const
{
    for (std::size_t i = 0; i < this->pts.size() - 1; i++)
    {
        if (this->pts[i] == this->pts.back())
        {
            return true;
        }
    }

    return false;
}

bool gs::Snake::changeDirection()
{
    if (gs::Utils::kbhit() == true)
    {
        switch (getch())
        {
        case -32:
            switch (getch())
            {
            case KEY_UP:
                if (this->direction != gs::Direction::DOWN)
                {
                    this->direction = gs::Direction::UP;
                }
                break;
            case KEY_DOWN:
                if (this->direction != gs::Direction::UP)
                {
                    this->direction = gs::Direction::DOWN;
                }
                break;
            case KEY_LEFT:
                if (this->direction != gs::Direction::RIGHT)
                {
                    this->direction = gs::Direction::LEFT;
                }
                break;
            case KEY_RIGHT:
                if (this->direction != gs::Direction::LEFT)
                {
                    this->direction = gs::Direction::RIGHT;
                }
                break;
            default:
                break;
            }
            return true;

        case KEY_EXIT: // ESC
            return false;

        default:
            return true;
        }
    }

    return true;
}

bool gs::Snake::canEatFood(const gs::Food& food) const
{
    return this->pts.back() == food.getPos();
}

bool gs::Snake::canEatBigFood(const gs::Food& bigFood) const
{
    if (this->pts.back() == bigFood.getBigPos())
    {
        gs::Utils::setCursorPosition(1, 0);
        std::cout << "                                                            ";
        return true;
    }
  
    return false;
}
