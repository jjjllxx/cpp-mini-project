#pragma once

namespace gs
{
namespace Utils
{
    void setWindowSize(const int cols, const int lines);
    void setCursorPosition(const int x, const int y);
    void setColor(const int colorID);
    void setBackColor();
    void initConsole();
    void endConsole();
    
    bool kbhit();
}
} // namespace gs