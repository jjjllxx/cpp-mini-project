#include "Scene.h"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory.h>
#include <unordered_set>
#include <vector>

#include "Common.h"
#include "I18n.h"
#include "Utility.h"

sdk::Scene::Scene() :
    curPt({ 0, 0 }),
    map(9, std::vector<sdk::PointValue>(9))
{
}

void sdk::Scene::show() const
{
    sdk::Utility::cls();
    sdk::printUnderline(this->curPt);

    for (int row = 0; row < static_cast<int>(this->map.size()); ++row)
    {
        sdk::printRow(this->map[row]);
        sdk::printUnderline(this->curPt, row);
    }
}

void sdk::Scene::setMode(const sdk::KeyMode mode)
{
    switch (mode)
    {
    case KeyMode::NORMAL:
        this->keyMap = sdk::Normal {};
        break;

    case KeyMode::VIM:
        this->keyMap = sdk::Vim {};
        break;
    }
}

bool sdk::Scene::setCurValue(const int curVal, int& preVal)
{
    if (const sdk::PointValue pt = this->map[this->curPt.x][this->curPt.y];
        pt.isErased == true)
    {
        preVal                                        = pt.value;

        this->map[this->curPt.x][this->curPt.y].value = curVal;
        return true;
    }

    return false;
}

// 选择count个格子清空
void sdk::Scene::eraseRandomGrids(const int count)
{
    std::vector<int> grids(81);
    for (int i = 0; i < 81; ++i)
    {
        grids[i] = i;
    }

    for (int i = 0; i < count; ++i)
    {
        const unsigned int r                           = sdk::Utility::random(0, static_cast<int>(grids.size() - 1));
        this->map[grids[r] / 9][grids[r] % 9].value    = sdk::UNSELECTED;
        this->map[grids[r] / 9][grids[r] % 9].isErased = true;
        grids.erase(grids.begin() + r);
    }
}

bool sdk::Scene::save(const std::string& filename)
{
    if (std::filesystem::exists(std::filesystem::path(filename)))
    {
        return false;
    }

    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    for (const std::vector<sdk::PointValue>& row : this->map)
    {
        for (const sdk::PointValue& pv : row)
        {
            fs << pv.value << ' ' << static_cast<int>(pv.isErased) << '\n';
        }
    }
    fs << this->curPt.x << ' ' << this->curPt.y << '\n';

    fs << this->commands.size() << '\n';
    for (const Command& cmd : this->commands)
    {
        fs << cmd.pos.x << ' ' << cmd.pos.y << ' '
           << cmd.preValue << ' '
           << cmd.curValue << '\n';
    }

    fs.close();
    return true;
}

bool sdk::Scene::load(const std::string& filename)
{
    if (std::filesystem::exists(std::filesystem::path(filename)) == false)
    {
        return false;
    }

    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    for (std::vector<sdk::PointValue>& row : map)
    {
        for (sdk::PointValue& pv : row)
        {
            int tmpState = 0;
            fs >> pv.value >> tmpState;
            tmpState == 1 ? pv.isErased = true : pv.isErased = false;
        }
    }

    fs >> this->curPt.x >> this->curPt.y;

    int commandSize = 0;
    fs >> commandSize;
    for (int i = 0; i < commandSize; i++)
    {
        Command cmd {};

        fs >> cmd.pos.x >> cmd.pos.y >> cmd.preValue >> cmd.curValue;
        this->commands.push_back(cmd);
    }
    return true;
}

void sdk::Scene::play()
{
    sdk::Scene::show();

    char key = '\0';
    while (true)
    {
        key = sdk::Utility::getch();
        if (key >= '0' && key <= '9')
        {
            Command cmd {};
            cmd.pos = this->curPt;
            if (sdk::Scene::setCurValue(key - '0', cmd.preValue) == false)
            {
                std::cout << "(" << this->curPt.x << "," << this->curPt.y << ")" <<"this number can't be modified." << '\n';
            }
            else
            {
                this->commands.push_back(cmd); // XXX: move without move constructor
                sdk::Scene::show();
                continue;
            }
        }

        if (key == this->keyMap.ESC)
        {
            sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::ASK_QUIT));
            std::string strInput;
            std::cin >> strInput;
            if (strInput[0] == 'y' || strInput[0] == 'Y')
            {
                sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::ASK_SAVE));
                std::cin >> strInput;
                if (strInput[0] == 'y' || strInput[0] == 'Y')
                {
                    while (true)
                    {
                        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::ASK_SAVE_PATH));
                        std::cin >> strInput;
                        if (sdk::Scene::save(strInput) == true)
                        {
                            break;
                        }
                        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::FILE_EXIST_ERROR));
                    }
                }
                exit(0);
            }
            else
            {
                sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::CONTINUE));
            }
        }
        else if (key == this->keyMap.U)
        {
            if (this->commands.empty() == true)
            {
                sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::UNDO_ERROR));
            }
            else
            {
                sdk::Scene::setPointValue(this->commands.back().pos, this->commands.back().preValue);
                this->commands.pop_back();
                sdk::Scene::show();
            }
        }
        else if (key == this->keyMap.LEFT)
        {
            this->curPt.y = (this->curPt.y - 1) < 0 ? 0 : this->curPt.y - 1;
            sdk::Scene::show();
        }
        else if (key == this->keyMap.RIGHT)
        {
            this->curPt.y = (this->curPt.y + 1) > 8 ? 8 : this->curPt.y + 1;
            sdk::Scene::show();
        }
        else if (key == this->keyMap.DOWN)
        {
            this->curPt.x = (this->curPt.x + 1) > 8 ? 8 : this->curPt.x + 1;
            sdk::Scene::show();
        }
        else if (key == this->keyMap.UP)
        {
            this->curPt.x = (this->curPt.x - 1) < 0 ? 0 : this->curPt.x - 1;
            sdk::Scene::show();
        }
        else if (key == this->keyMap.ENTER)
        {
            if (sdk::Scene::isComplete() == true)
            {
                sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::CONGRATULATION));
                getchar();
                exit(0);
            }
            else
            {
                sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::NOT_COMPLETED));
            }
        }
    }
}

// 一个场景可以多次被初始化
void sdk::Scene::generate()
{
    std::vector<std::vector<int>> matrix(9, std::vector<int>(9));

    // 初始化三个nuit
    // 2 6 5 | 0 0 0 | 0 0 0
    // 3 4 1 | 0 0 0 | 0 0 0
    // 8 9 7 | 0 0 0 | 0 0 0
    // ---------------------
    // 0 0 0 | 1 9 4 | 0 0 0
    // 0 0 0 | 8 3 6 | 0 0 0
    // 0 0 0 | 5 2 7 | 0 0 0
    // ---------------------
    // 0 0 0 | 0 0 0 | 3 4 5
    // 0 0 0 | 0 0 0 | 9 6 2
    // 0 0 0 | 0 0 0 | 7 8 1
    for (const int num : {0, 3,6})
    {
        std::vector<int> unit = sdk::Utility::shuffle_unit();
        for (int i = num; i < num + 3; i++)
        {
            for (int j = num; j < num + 3; j++)
            {
                matrix[i][j] = unit.back();
                unit.pop_back();
            }
        }
    }

    // 统计空格数量
    std::vector<std::tuple<int, int>> emptyUnits;
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (matrix[i][j] == 0)
            {
                emptyUnits.emplace_back(i, j);
            }
        }
    }

    // 逐个填充空格
    std::map<std::string, std::vector<int>> availableNum;

    std::size_t fullNum = 0;
    while (fullNum < emptyUnits.size())
    {
        const int row = std::get<0>(emptyUnits[fullNum]);
        const int col = std::get<1>(emptyUnits[fullNum]);

        std::vector<int>  ableUnits;
        const std::string key = std::to_string(row) + "x" + std::to_string(col);
        if (availableNum.find(key) == availableNum.end())
        {
            // 九宫格
            std::vector<int> ableUnits = sdk::Utility::get_unit();
            for (int i = row / 3 * 3; i < row / 3 * 3 + 3; i++)
            {
                for (int j = col / 3 * 3; j < col / 3 * 3 + 3; j++)
                {
                    ableUnits.erase(std::remove(ableUnits.begin(), ableUnits.end(), matrix[i][j]), ableUnits.end());
                }
            }
            // 行
            for (int i = 0; i < 9; i++)
            {
                if (matrix[row][i] != 0)
                {
                    ableUnits.erase(std::remove(ableUnits.begin(), ableUnits.end(), matrix[row][i]), ableUnits.end());
                }
            }
            // 列
            for (int i = 0; i < 9; i++)
            {
                if (matrix[i][col] != 0)
                {
                    ableUnits.erase(std::remove(ableUnits.begin(), ableUnits.end(), matrix[i][col]), ableUnits.end());
                }
            }
            availableNum[key] = ableUnits;
        }
        else
        {
            ableUnits = availableNum[key];
        }

        // 如果没有可用的数字，则回溯
        if (availableNum[key].empty() == true)
        {
            fullNum -= 1;
            if (availableNum.find(key) != availableNum.end())
            {
                availableNum.erase(key);
            }
            matrix[row][col] = 0;
            continue;
        }

        matrix[row][col] = availableNum[key].back();
        availableNum[key].pop_back();
        fullNum += 1;
    }

    // 填入场景
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            this->map[row][col].value = matrix[row][col];
        }
    }
}

bool sdk::Scene::setPointValue(const Point& pt, const int val)
{
    if (const sdk::PointValue pv = this->map[pt.x][pt.y];
        pv.isErased == true)
    {
        this->curPt                 = pt;
        this->map[pt.x][pt.y].value = val;
        return true;
    }

    return false;
}

bool sdk::isBlockComplete(const std::vector<sdk::PointValue>& numbers)
{
    std::unordered_set<int> st;

    for (const sdk::PointValue& pv : numbers)
    {
        if (pv.value == sdk::UNSELECTED || st.find(pv.value) != st.end())
        {
            return false;
        }
        st.insert(pv.value);
    }

    return true;
}

void sdk::printRow(const std::vector<sdk::PointValue>& numbers)
{
    std::cout << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED) << sdk::PIPE << sdk::Utility::getModifier() << " ";
    for (std::size_t i = 0; i < numbers.size(); ++i)
    {
        const sdk::PointValue& pv = numbers[i];
        if ((i + 1) % 3 == 0)
        {
            if (pv.value == sdk::UNSELECTED)
            {
                std::cout << ' ' << " " << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED) << sdk::PIPE << sdk::Utility::getModifier() << " ";
            }
            else
            {
                if (pv.isErased == true)
                {
                    std::cout << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_GREEN) << pv.value
                              << sdk::Utility::getModifier() << " "
                              << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED) << sdk::PIPE
                              << sdk::Utility::getModifier() << " ";
                }
                else
                {
                    std::cout << pv.value << " " << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED)
                              << sdk::PIPE << sdk::Utility::getModifier() << " ";
                }
            }
        }
        else
        {
            if (pv.value == sdk::UNSELECTED)
            {
                std::cout << ' ' << " " << sdk::PIPE << " ";
            }
            else
            {
                if (pv.isErased == true)
                {
                    std::cout << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_GREEN) << pv.value
                              << sdk::Utility::getModifier() << " " << sdk::PIPE << " ";
                }
                else
                {
                    std::cout << pv.value << " " << sdk::PIPE << " ";
                }
            }
        }
    }
    std::cout << '\n';
}

void sdk::printUnderline(const sdk::Point& curPt, const int line_no)
{
    for (int col = 0; col < 9; ++col)
    {
        if (col % 3 == 0 || line_no == -1 || (line_no + 1) % 3 == 0)
        {
            std::cout << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED) << sdk::CORNER << sdk::Utility::getModifier();
        }
        else
        {
            std::cout << sdk::CORNER;
        }

        const std::string symbol = (curPt.x == line_no && curPt.y == col) ? sdk::ARROW : sdk::LINE;
        if (line_no == -1 || (line_no + 1) % 3 == 0)
        {
            std::cout << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED) << sdk::LINE << symbol << sdk::LINE << sdk::Utility::getModifier();
        }
        else
        {
            std::cout << sdk::LINE << symbol << sdk::LINE;
        }
    }
    std::cout << sdk::Utility::getModifier(sdk::ColorCode::BOLD, sdk::ColorCode::BG_DEFAULT, sdk::ColorCode::FG_RED) << sdk::CORNER << sdk::Utility::getModifier() << '\n';
}

bool sdk::Scene::isComplete()
{
    for (const std::vector<sdk::PointValue>& row : this->map)
    {
        if (sdk::isBlockComplete(row) == false)
        {
            return false;
        }
    }

    for (int row = 0; row < 9; ++row)
    {
        std::vector<sdk::PointValue> numbers;
        numbers.reserve(9);

        for (int col = 0; col < 9; ++col)
        {
            numbers.push_back(this->map[row][col]);
        }

        if (sdk::isBlockComplete(numbers) == false)
        {
            return false;
        }
    }

    const std::vector<int> offset = { 0, 1, 2, 9, 10, 11, 18, 19, 20 };
    for (int row = 0; row < 9; row += 3)
    {
        for (int col = 0; col < 9; col += 3)
        {
            const int                    base = (row * 9) + col;
            std::vector<sdk::PointValue> numbers;
            numbers.reserve(9);

            for (const int os : offset)
            {
                numbers.push_back(this->map[(base + os) / 9][(base + os) % 9]);
            }

            if (sdk::isBlockComplete(numbers) == false)
            {
                return false;
            }
        }
    }

    return true;
}