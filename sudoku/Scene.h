#pragma once

#include "Common.h"
#include <string>
#include <vector>

namespace sdk
{
class Scene
{
public:
    Scene();

    void generate();
    void show() const;
    void play();
    bool save(const std::string& filename);
    bool load(const std::string& filename);
    void setMode(const sdk::KeyMode mode);
    void eraseRandomGrids(const int count);

private:
    bool isComplete();
    bool setCurValue(const int curVal, int& preVal);
    bool setPointValue(const sdk::Point& pt, const int val);

    sdk::KeyMap keyMap {};
    sdk::Point  curPt;

    std::vector<std::vector<sdk::PointValue>> map;
    std::vector<sdk::Command>    commands;
};

void printUnderline(const sdk::Point& curPt, const int line_no = -1);
void printRow(const std::vector<sdk::PointValue>& numbers);
bool isBlockComplete(const std::vector<sdk::PointValue>& numbers);

} // namespace sdk
