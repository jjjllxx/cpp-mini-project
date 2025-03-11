#pragma once
#include <cstdint>
#include <string>

namespace sdk
{
static const unsigned int UNSELECTED = 0;

static const std::string CORNER = "\u254B";
static const std::string LINE   = "\u2501";
static const std::string PIPE   = "\u2503";
static const std::string ARROW  = "^";

enum class ColorCode : std::int8_t
{
    BOLD  = 1,
    RESET = 0,

    BG_BLACK      = 40,
    BG_RED        = 41,
    BG_GREEN      = 42,
    BG_YELLOW     = 43,
    BG_BLUE       = 44,
    BG_MAGENTA    = 45,
    BG_CYAN       = 46,
    BG_LIGHT_GRAY = 47, // 实际是白色，终端为正常显示会进行调整
    BG_DEFAULT    = 49,

    FG_BLACK         = 30,
    FG_RED           = 31,
    FG_GREEN         = 32,
    FG_YELLOW        = 33,
    FG_BLUE          = 34,
    FG_MAGENTA       = 35,
    FG_CYAN          = 36,
    FG_LIGHT_GRAY    = 37,
    FG_DEFAULT       = 39,
    FG_DARK_GRAY     = 90,
    FG_LIGHT_RED     = 91,
    FG_LIGHT_GREEN   = 92,
    FG_LIGHT_YELLOW  = 93,
    FG_LIGHT_BLUE    = 94,
    FG_LIGHT_MAGENTA = 95,
    FG_LIGHT_CYAN    = 96,
    FG_WHITE         = 97,

};

enum class Difficulty : std::int8_t
{
    EASY = 1,
    NORMAL,
    HARD
};  

enum class KeyMode : std::int8_t
{
    NORMAL = 1,
    VIM
};

struct KeyMap
{
    char ESC = 0x1B;
    char U   = 0x75;
    char UP {};
    char LEFT {};
    char DOWN {};
    char RIGHT {};
    char ENTER = 0x0D;
};

struct Normal : KeyMap
{
    Normal()
    {
        UP    = 0x77;
        LEFT  = 0x61;
        DOWN  = 0x73;
        RIGHT = 0x64;
    }
};

struct Vim : KeyMap
{
    Vim()
    {
        UP    = 0x6B;
        LEFT  = 0x68;
        DOWN  = 0x6A;
        RIGHT = 0x6C;
    }
};

struct Point
{
    int x;
    int y;
};

struct PointValue
{
    bool isErased = false;
    int  value    = sdk::UNSELECTED;
};

struct Command
{
    sdk::Point pos;

    int preValue;
    int curValue;
};
} // namespace sdk