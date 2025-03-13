#include "Controller.h"
#include "Food.h"
#include "Map.h"
#include "Snake.h"
#include "StartInterface.h"
#include "Utils.h"
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

void gs::Controller::init()
{
    gs::Utils::setWindowSize(41, 32);
    gs::Utils::setColor(2);

    gs::StartInterface start;
    start.showAll();

    gs::Utils::setCursorPosition(13, 26);
    std::cout << "Press any key to start... ";
    gs::Utils::setCursorPosition(13, 27);

    getch();
}

void gs::Controller::selectMode()
{
    gs::Utils::setColor(3);
    gs::Utils::setCursorPosition(13, 26);
    std::cout << "                          ";
    gs::Utils::setCursorPosition(13, 27);
    std::cout << "                          ";
    gs::Utils::setCursorPosition(6, 21);
    std::cout << "Please select game difficulty";
    gs::Utils::setCursorPosition(6, 22);
    std::cout << "(Use the up and down arrows to select, press Enter to confirm)";
    gs::Utils::setCursorPosition(27, 22);
    gs::Utils::setBackColor();
    std::cout << "Easy Mode";
    gs::Utils::setCursorPosition(27, 24);
    gs::Utils::setColor(3);
    std::cout << "Normal Mode";
    gs::Utils::setCursorPosition(27, 26);
    std::cout << "Hard Mode";
    gs::Utils::setCursorPosition(27, 28);
    std::cout << "Hell Mode";
    gs::Utils::setCursorPosition(0, 31);

    this->mode  = 1;
    this->score = 0;

    int ch = 0;

    bool isEnterPressed = false;
    while ((ch = getch()) != 0)
    {
        switch (ch)
        {
        case KEY_UP:
            if (this->mode > 1)
            {
                switch (this->mode)
                {
                case 2:
                    gs::Utils::setCursorPosition(27, 22);
                    gs::Utils::setBackColor();
                    std::cout << "Easy Mode";

                    gs::Utils::setCursorPosition(27, 24);
                    gs::Utils::setColor(3);
                    std::cout << "Normal Mode";

                    --this->mode;
                    break;
                case 3:
                    gs::Utils::setCursorPosition(27, 24);
                    gs::Utils::setBackColor();
                    std::cout << "Normal Mode";

                    gs::Utils::setCursorPosition(27, 26);
                    gs::Utils::setColor(3);
                    std::cout << "Hard Mode";

                    --this->mode;
                    break;
                case 4:
                    gs::Utils::setCursorPosition(27, 26);
                    gs::Utils::setBackColor();
                    std::cout << "Hard Mode";

                    gs::Utils::setCursorPosition(27, 28);
                    gs::Utils::setColor(3);
                    std::cout << "Hell Mode";

                    --this->mode;
                    break;
                default:
                    break;
                }
            }
            break;

        case KEY_DOWN: // DOWN
            if (this->mode < 4)
            {
                switch (this->mode)
                {
                case 1:
                    gs::Utils::setCursorPosition(27, 24);
                    gs::Utils::setBackColor();
                    std::cout << "Normal Mode";
                    gs::Utils::setCursorPosition(27, 22);
                    gs::Utils::setColor(3);
                    std::cout << "Easy Mode";

                    ++this->mode;
                    break;
                case 2:
                    gs::Utils::setCursorPosition(27, 26);
                    gs::Utils::setBackColor();
                    std::cout << "Hard Mode";
                    gs::Utils::setCursorPosition(27, 24);
                    gs::Utils::setColor(3);
                    std::cout << "Normal Mode";

                    ++this->mode;
                    break;
                case 3:
                    gs::Utils::setCursorPosition(27, 28);
                    gs::Utils::setBackColor();
                    std::cout << "Hell Mode";
                    gs::Utils::setCursorPosition(27, 26);
                    gs::Utils::setColor(3);
                    std::cout << "Hard Mode";

                    ++this->mode;
                    break;
                default:
                    break;
                }
            }
            break;

        case KEY_ENTER: // Enter
            isEnterPressed = true;
            break;

        default:
            break;
        }

        if (isEnterPressed == true)
        {
            break;
        }

        gs::Utils::setCursorPosition(0, 31);
    }

    this->interval = (5 - this->mode) * 35;
}

void gs::Controller::drawGame() const
{
    system("clear");

    gs::Utils::setColor(3);
    const gs::Map initMap;
    initMap.showMap();

    gs::Utils::setColor(3);
    gs::Utils::setCursorPosition(33, 1);
    std::cout << "Greedy Snake";
    gs::Utils::setCursorPosition(34, 2);
    std::cout << "̰贪吃蛇";
    gs::Utils::setCursorPosition(31, 4);
    std::cout << "Difficulty:";
    gs::Utils::setCursorPosition(36, 5);
    switch (this->mode)
    {
    case 1:
        std::cout << "Easy Mode";
        break;
    case 2:
        std::cout << "Normal Mode";
        break;
    case 3:
        std::cout << "Hard Mode";
        break;
    case 4:
        std::cout << "Hell Mode";
        break;
    default:
        break;
    }
    gs::Utils::setCursorPosition(31, 7);
    std::cout << "Score:";
    gs::Utils::setCursorPosition(37, 8);
    std::cout << "     0";
    gs::Utils::setCursorPosition(33, 13);
    std::cout << " Move with arrow keys";
    gs::Utils::setCursorPosition(33, 15);
    std::cout << " ESC to pause";
}

bool gs::Controller::playGame()
{
    gs::Snake snake;
    gs::Food  food;
    gs::Utils::setColor(6);

    snake.initSnake();
    srand((unsigned) time(nullptr));
    food.drawFood(snake);

    while (snake.isOverEdge() == false && snake.hasHitItself() == false)
    {
        if (snake.changeDirection() == false)
        {
            switch (gs::Controller::showMenu())
            {
            case 1:
                break;
            case 2:
                return true;
            case 3:
                return false;

            default:
                break;
            }
        }

        if (snake.canEatFood(food) == true)
        {
            snake.moveWithEat();
            gs::Controller::updateScore(1);
            gs::Controller::rewriteScore();
            food.drawFood(snake);
        }
        else
        {
            snake.moveWithoutEat();
        }

        if (snake.canEatBigFood(food) == true)
        {
            snake.moveWithEat();
            food.clearBigFood();
            gs::Controller::updateScore(food.getProgressBar() / 5);
            gs::Controller::rewriteScore();
        }

        if (food.hasBigFood() == true)
        {
            food.flashBigFood();
        }

        usleep(this->interval * 1000);
    }

    return !gs::Controller::endGame();
}

void gs::Controller::updateScore(const int coef)
{
    this->score += this->mode * 10 * coef;
}

void gs::Controller::rewriteScore() const
{
    gs::Utils::setCursorPosition(37, 8);
    gs::Utils::setColor(11);
    
    int bit = 0;
    int tmpScore = this->score;
    while (tmpScore != 0)
    {
        ++bit;
        tmpScore /= 10;
    }

    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " ";
    }

    std::cout << this->score;
}

int gs::Controller::showMenu()
{
    gs::Utils::setColor(11);
    gs::Utils::setCursorPosition(32, 19);
    std::cout << "Menu: ";
    usleep(100 * 1000);
    gs::Utils::setCursorPosition(34, 21);
    gs::Utils::setBackColor();
    std::cout << "Continue Game";
    usleep(100 * 1000);
    gs::Utils::setCursorPosition(34, 23);
    gs::Utils::setColor(11);
    std::cout << "Restart Game";
    usleep(100 * 1000);
    gs::Utils::setCursorPosition(34, 25);
    std::cout << "Exit Game";
    gs::Utils::setCursorPosition(0, 31);

    int  ch             = 0;
    int  keyPos         = 1;
    bool isEnterPressed = false;
    while ((ch = getch()) != 0)
    {
        switch (ch)
        {
        case KEY_UP: // UP
            if (keyPos > 1)
            {
                switch (keyPos)
                {
                case 2:
                    gs::Utils::setCursorPosition(34, 21);
                    gs::Utils::setBackColor();
                    std::cout << "Continue Game";
                    gs::Utils::setCursorPosition(34, 23);
                    gs::Utils::setColor(11);
                    std::cout << "Restart Game";

                    --keyPos;
                    break;
                case 3:
                    gs::Utils::setCursorPosition(34, 23);
                    gs::Utils::setBackColor();
                    std::cout << "Restart Game";
                    gs::Utils::setCursorPosition(34, 25);
                    gs::Utils::setColor(11);
                    std::cout << "Exit Game";

                    --keyPos;
                    break;
                default:
                    break;
                }
            }
            break;

        case KEY_DOWN:
            if (keyPos < 3)
            {
                switch (keyPos)
                {
                case 1:
                    gs::Utils::setCursorPosition(34, 23);
                    gs::Utils::setBackColor();
                    std::cout << "Restart Game";
                    gs::Utils::setCursorPosition(34, 21);
                    gs::Utils::setColor(11);
                    std::cout << "Continue Game";

                    ++keyPos;
                    break;
                case 2:
                    gs::Utils::setCursorPosition(34, 25);
                    gs::Utils::setBackColor();
                    std::cout << "Exit Game";
                    gs::Utils::setCursorPosition(34, 23);
                    gs::Utils::setColor(11);
                    std::cout << "Restart Game";

                    ++keyPos;
                    break;
                default:
                    break;
                }
            }
            break;

        case KEY_ENTER:
            isEnterPressed = true;
            break;

        default:
            break;
        }

        if (isEnterPressed)
        {
            break;
        }
        gs::Utils::setCursorPosition(0, 31);
    }

    if (keyPos == 1)
    {
        gs::Utils::setCursorPosition(32, 19);
        std::cout << "      ";
        gs::Utils::setCursorPosition(34, 21);
        std::cout << "        ";
        gs::Utils::setCursorPosition(34, 23);
        std::cout << "        ";
        gs::Utils::setCursorPosition(34, 25);
        std::cout << "        ";
    }

    return keyPos;
}

void gs::Controller::gameLoop()
{
    gs::Controller::init();
    while (true)
    {
        gs::Controller::selectMode();
        gs::Controller::drawGame();

        if (gs::Controller::playGame() == false)
        {
            break;
        }

        system("clear");
    }
}

bool gs::Controller::endGame() const
{
    usleep(500 * 1000);
    gs::Utils::setColor(11);
    gs::Utils::setCursorPosition(10, 8);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 9);
    std::cout << " ┃               Game Over !!!              ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 10);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 11);
    std::cout << " ┃          Sorry! The Game is End          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 12);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 13);
    std::cout << " ┃            Your Score is:                ┃";
    gs::Utils::setCursorPosition(24, 13);
    std::cout << this->score;
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 14);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 15);
    std::cout << " ┃   Try one more time?                     ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 16);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 17);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 18);
    std::cout << " ┃    Yes                     No            ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 19);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(9, 20);
    std::cout << " ┃                                          ┃";
    usleep(30 * 1000);
    gs::Utils::setCursorPosition(10, 21);
    std::cout << "━━━━━━━━━━━━━━━━━━━━━━";

    usleep(100 * 1000);
    gs::Utils::setCursorPosition(12, 18);
    gs::Utils::setBackColor();
    std::cout << "Yes";
    gs::Utils::setCursorPosition(0, 31);

    int  ch             = 0;
    int  keyPos         = 1;
    bool isEnterPressed = false;

    while ((ch = getch()) != 0)
    {
        switch (ch)
        {
        case 75: // LEFT
            if (keyPos > 1)
            {
                gs::Utils::setCursorPosition(12, 18);
                gs::Utils::setBackColor();
                std::cout << "Yes";
                gs::Utils::setCursorPosition(20, 18);
                gs::Utils::setColor(11);
                std::cout << "No";
                --keyPos;
            }
            break;

        case 77: // RIGHT
            if (keyPos < 2)
            {
                gs::Utils::setCursorPosition(20, 18);
                gs::Utils::setBackColor();
                std::cout << "No";
                gs::Utils::setCursorPosition(12, 18);
                gs::Utils::setColor(11);
                std::cout << "Yes";
                ++keyPos;
            }
            break;

        case 13:
            isEnterPressed = true;
            break;

        default:
            break;
        }

        gs::Utils::setCursorPosition(0, 31);

        if (isEnterPressed == true)
        {
            break;
        }
    }

    gs::Utils::setColor(11);

    return keyPos == 1 ? false : true;
}