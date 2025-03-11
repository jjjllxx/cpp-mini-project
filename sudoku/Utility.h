#pragma once

#include <string>
#include <vector>
#include "Common.h"

namespace sdk
{

namespace Utility
{
    unsigned int random(const int begin, const int end);
    std::vector<int> get_unit();
    std::vector<int> shuffle_unit();
    void message(const char* msg = "", bool lf = true);
    void message(const std::string& msg, bool lf = true);
    char getch();
    void cls();

    std::string getModifier(const sdk::ColorCode md = sdk::ColorCode::RESET,
                                  const sdk::ColorCode bg = sdk::ColorCode::BG_DEFAULT,
                                  const sdk::ColorCode fg = sdk::ColorCode::FG_DEFAULT);
} // namespace Utility
} // namespace sdk
