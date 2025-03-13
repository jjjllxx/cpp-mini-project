#pragma once

#include "Point.h"

namespace gs
{
class Snake;

class Food
{
public:
    void drawFood(const Snake& snake);
    void drawBigFood(const Snake& snake);

    void flashBigFood();
    void clearBigFood();

    bool hasBigFood() const;
    int  getProgressBar() const;

    gs::Point getPos() const;
    gs::Point getBigPos() const;

private:
    bool hasBig     = false;
    bool isFlashing = false;

    int cnt         = 0;
    int progressBar = 0;

    gs::Point pos    = gs::Point(0, 0);
    gs::Point bigPos = gs::Point(0, 0);
};
} // namespace gs