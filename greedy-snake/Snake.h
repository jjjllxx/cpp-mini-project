#pragma once

#include "Food.h"
#include "Point.h"
#include <cstdint>
#include <deque>

namespace gs
{
class Food;

enum class Direction : std::int8_t
{
    INVALID = -1,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake
{
public:
    Snake()
    {
        pts.emplace_back(14, 8);
        pts.emplace_back(15, 8);
        pts.emplace_back(16, 8);
    }
    
    void initSnake();
    void moveWithEat();
    void moveWithoutEat();
    bool isInSnake(const gs::Point& pt) const;
    bool isOverEdge() const;
    bool hasHitItself() const;
    bool changeDirection();
    bool canEatFood(const gs::Food& food) const;
    bool canEatBigFood(const gs::Food& bigFood) const;

private:
    std::deque<gs::Point> pts;

    gs::Direction direction = gs::Direction::DOWN;
};
} // namespace gs
