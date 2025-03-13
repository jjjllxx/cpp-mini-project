#include "Point.h"
#include "Utils.h"
#include <iostream>

gs::Point::Point(const int x, const int y) :
    x(x), y(y)
{
}

void gs::Point::showSquare() const
{
    gs::Utils::setCursorPosition(this->x, this->y);
    std::cout << "■";
}

void gs::Point::showCircular() const 
{
    gs::Utils::setCursorPosition(this->x, this->y);
    std::cout << "●";
}

void gs::Point::clear() const 
{
    gs::Utils::setCursorPosition(this->x, this->y);
    std::cout << "  ";
}

void gs::Point::updatePos(const int x, const int y) 
{
    this->x = x;
    this->y = y;
}

bool gs::Point::operator==(const gs::Point& pt) const
{
    return pt.x == this->x && pt.y == this->y;
}

bool gs::Point::operator!=(const Point& pt) const
{
    return pt.x != this->x || pt.y != this->y;
}

int gs::Point::getX() const
{
    return this->x;
}

int gs::Point::getY() const
{
    return this->y;
}