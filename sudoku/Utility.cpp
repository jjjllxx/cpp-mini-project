#include "Utility.h"

#include <algorithm>
#include <iostream>
#include <random>

// not real random,return number between [begin,end]
unsigned int sdk::Utility::random(const int begin, const int end)
{
    std::random_device rd;
    std::mt19937       g(rd());
    return std::uniform_int_distribution<unsigned int>(begin, end)(g);
}

std::vector<int> sdk::Utility::get_unit()
{
    return std::vector<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
}

std::vector<int> sdk::Utility::shuffle_unit()
{
    std::vector<int>   unit = sdk::Utility::get_unit();
    std::random_device rd;
    std::mt19937       g(rd());
    std::shuffle(unit.begin(), unit.end(), g);
    return unit;
}

void sdk::Utility::message(const char* msg, bool lf)
{
    std::cout << msg;
    if (lf)
    {
        std::cout << '\n';
    }
}

void sdk::Utility::message(const std::string& msg, bool lf)
{
    message(msg.c_str(), lf);
}

#ifdef __linux__
#    include <cstdio>
#    include <fcntl.h>
#    include <termio.h>
#elif __APPLE__
#    include <fcntl.h>
#    include <termios.h>
#endif

char sdk::Utility::getch()
{
    struct termios tmtemp {};
    struct termios tm {};
    int            c  = 0;
    int            fd = 0;
    if (tcgetattr(fd, &tm) != 0)
    { /*获取当前的终端属性设置，并保存到tm结构体中*/
        return -1;
    }
    tmtemp = tm;
    cfmakeraw(&tmtemp); /*将tetemp初始化为终端原始模式的属性设置*/
    if (tcsetattr(fd, TCSANOW, &tmtemp) != 0)
    { /*将终端设置为原始模式的设置*/
        return -1;
    }
    c = getchar();
    if (c == 27) /* ESC返回27，上下左右为(27,91,xx) 与ESC的27冲突 */
    {
        int backFlags = fcntl(fd, F_GETFL); // NOLINT
        /*将fd设置为非阻塞的，没有输入时可以立即返回*/
        fcntl(fd, F_SETFL, backFlags | O_NONBLOCK); // NOLINT
        c = getchar();
        if (c == EOF)
        {
            c = 27;
        }
        else
        {
            while ((c = getchar()) != EOF)
            {
            }
        }
        fcntl(fd, F_SETFL, backFlags); // NOLINT
    }
    if (tcsetattr(fd, TCSANOW, &tm) != 0)
    { /*接收字符完毕后将终端设置回原来的属性*/
        return 0;
    }
    return static_cast<char>(c);
}

void sdk::Utility::cls()
{
    system("clear");
}

std::string sdk::Utility::getModifier(const sdk::ColorCode md,
                                      const sdk::ColorCode bg,
                                      const sdk::ColorCode fg)
{
    std::string os;

    os += "\033[";
    os += std::to_string(static_cast<int>(md));
    os += ";";
    os += std::to_string(static_cast<int>(bg));
    os += ";";
    os += std::to_string(static_cast<int>(fg));
    os += "m";

    return os;
}