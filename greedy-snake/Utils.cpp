#include "Utils.h"
#include <cstdio>
#include <cstdlib>
#include <ncurses.h>

void gs::Utils::setWindowSize(int cols, int lines)
{
    printf("\033]0;贪吃蛇\007");              // set window title
    printf("\033[8;%d;%dt", lines, cols * 2); // Resize terminal window
}

void gs::Utils::setCursorPosition(const int x, const int y)
{
    printf("\033[%d;%dH", y + 1, (x * 2) + 1); // Move cursor to (x, y)
}

void gs::Utils::setColor(int colorID)
{
    printf("\033[%dm", colorID); // set text color
}

void gs::Utils::setBackColor()
{
    printf("\033[44m"); // set background color to blue
}

void gs::Utils::initConsole() // 初始化 ncurses
{
    initscr();
    start_color();
    noecho();
    curs_set(0); // 隐藏光标
}

void gs::Utils::endConsole() // 关闭 ncurses
{
    endwin();
}

bool gs::Utils::kbhit()
{
    const int ch = getch();
    if (ch != ERR)
    {
        ungetch(ch);
        return true;
    }
    else
    {
        return false;
    }
}
