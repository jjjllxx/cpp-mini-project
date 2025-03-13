#pragma once

#include "Point.h"
#include <deque>
#include <vector>

namespace gs {
class StartInterface
{
public:
    StartInterface()
    {
        startSnake.emplace_back(0, 14); // E
        startSnake.emplace_back(1, 14);
        startSnake.emplace_back(2, 15);
        startSnake.emplace_back(3, 16);
        startSnake.emplace_back(4, 17);
        startSnake.emplace_back(5, 18);
        startSnake.emplace_back(6, 17);
        startSnake.emplace_back(7, 16);
        startSnake.emplace_back(8, 15);
        startSnake.emplace_back(9, 14);

        texts.emplace_back(-26, 14); // S
        texts.emplace_back(-25, 14);
        texts.emplace_back(-27, 15);
        texts.emplace_back(-26, 16);
        texts.emplace_back(-25, 17);
        texts.emplace_back(-27, 18);
        texts.emplace_back(-26, 18);

        texts.emplace_back(-23, 14); // N
        texts.emplace_back(-23, 15);
        texts.emplace_back(-23, 16);
        texts.emplace_back(-23, 17);
        texts.emplace_back(-23, 18);
        texts.emplace_back(-22, 15);
        texts.emplace_back(-21, 16);
        texts.emplace_back(-20, 17);
        texts.emplace_back(-19, 14);
        texts.emplace_back(-19, 15);
        texts.emplace_back(-19, 16);
        texts.emplace_back(-19, 17);
        texts.emplace_back(-19, 18);

        texts.emplace_back(-17, 18); // A
        texts.emplace_back(-16, 17);
        texts.emplace_back(-15, 16);
        texts.emplace_back(-14, 15);
        texts.emplace_back(-14, 16);
        texts.emplace_back(-13, 14);
        texts.emplace_back(-13, 16);
        texts.emplace_back(-12, 15);
        texts.emplace_back(-12, 16);
        texts.emplace_back(-11, 16);
        texts.emplace_back(-10, 17);
        texts.emplace_back(-9, 18);

        texts.emplace_back(-7, 14); // K
        texts.emplace_back(-7, 15);
        texts.emplace_back(-7, 16);
        texts.emplace_back(-7, 17);
        texts.emplace_back(-7, 18);
        texts.emplace_back(-6, 16);
        texts.emplace_back(-5, 15);
        texts.emplace_back(-5, 17);
        texts.emplace_back(-4, 14);
        texts.emplace_back(-4, 18);

        texts.emplace_back(-2, 14); // E
        texts.emplace_back(-2, 15);
        texts.emplace_back(-2, 16);
        texts.emplace_back(-2, 17);
        texts.emplace_back(-2, 18);
        texts.emplace_back(-1, 14);
        texts.emplace_back(-1, 16);
        texts.emplace_back(-1, 18);
        texts.emplace_back(0, 14);
        texts.emplace_back(0, 16);
        texts.emplace_back(0, 18);
    }

    void showSnakeAppear() const;
    void showSnakeMove();
    void showSnakeDisappear();
    void showText() const;
    void clearText();
    void showAll();

private:
    int animInterval = 50; // 动画的速度

    std::deque<gs::Point>  startSnake; // 开始动画中的蛇
    std::vector<gs::Point> texts;  // 开始动画中的文字
};
}