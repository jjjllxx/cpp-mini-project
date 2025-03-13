#pragma once

#include "Point.h"
#include <vector>

namespace gs
{
class Map
{
public:
    Map()
    {
        initMap.emplace_back(1, 1);
        initMap.emplace_back(2, 1);
        initMap.emplace_back(3, 1);
        initMap.emplace_back(4, 1);
        initMap.emplace_back(5, 1);
        initMap.emplace_back(6, 1);
        initMap.emplace_back(7, 1);
        initMap.emplace_back(8, 1);
        initMap.emplace_back(9, 1);
        initMap.emplace_back(10, 1);
        initMap.emplace_back(11, 1);
        initMap.emplace_back(12, 1);
        initMap.emplace_back(13, 1);
        initMap.emplace_back(14, 1);
        initMap.emplace_back(15, 1);
        initMap.emplace_back(16, 1);
        initMap.emplace_back(17, 1);
        initMap.emplace_back(18, 1);
        initMap.emplace_back(19, 1);
        initMap.emplace_back(20, 1);
        initMap.emplace_back(21, 1);
        initMap.emplace_back(22, 1);
        initMap.emplace_back(23, 1);
        initMap.emplace_back(24, 1);
        initMap.emplace_back(25, 1);
        initMap.emplace_back(26, 1);
        initMap.emplace_back(27, 1);
        initMap.emplace_back(28, 1);
        initMap.emplace_back(29, 1);
        initMap.emplace_back(30, 1);
        initMap.emplace_back(1, 2);
        initMap.emplace_back(30, 2);
        initMap.emplace_back(1, 3);
        initMap.emplace_back(30, 3);
        initMap.emplace_back(1, 4);
        initMap.emplace_back(30, 4);
        initMap.emplace_back(1, 5);
        initMap.emplace_back(30, 5);
        initMap.emplace_back(1, 6);
        initMap.emplace_back(30, 6);
        initMap.emplace_back(1, 7);
        initMap.emplace_back(30, 7);
        initMap.emplace_back(1, 8);
        initMap.emplace_back(30, 8);
        initMap.emplace_back(1, 9);
        initMap.emplace_back(30, 9);
        initMap.emplace_back(1, 10);
        initMap.emplace_back(30, 10);
        initMap.emplace_back(1, 11);
        initMap.emplace_back(30, 11);
        initMap.emplace_back(1, 12);
        initMap.emplace_back(30, 12);
        initMap.emplace_back(1, 13);
        initMap.emplace_back(30, 13);
        initMap.emplace_back(1, 14);
        initMap.emplace_back(30, 14);
        initMap.emplace_back(1, 15);
        initMap.emplace_back(30, 15);
        initMap.emplace_back(1, 16);
        initMap.emplace_back(30, 16);
        initMap.emplace_back(1, 17);
        initMap.emplace_back(30, 17);
        initMap.emplace_back(1, 18);
        initMap.emplace_back(30, 18);
        initMap.emplace_back(1, 19);
        initMap.emplace_back(30, 19);
        initMap.emplace_back(1, 20);
        initMap.emplace_back(30, 20);
        initMap.emplace_back(1, 21);
        initMap.emplace_back(30, 21);
        initMap.emplace_back(1, 22);
        initMap.emplace_back(30, 22);
        initMap.emplace_back(1, 23);
        initMap.emplace_back(30, 23);
        initMap.emplace_back(1, 24);
        initMap.emplace_back(30, 24);
        initMap.emplace_back(1, 25);
        initMap.emplace_back(30, 25);
        initMap.emplace_back(1, 26);
        initMap.emplace_back(30, 26);
        initMap.emplace_back(1, 27);
        initMap.emplace_back(30, 27);
        initMap.emplace_back(1, 28);
        initMap.emplace_back(30, 28);
        initMap.emplace_back(1, 29);
        initMap.emplace_back(30, 29);
        initMap.emplace_back(1, 30);
        initMap.emplace_back(2, 30);
        initMap.emplace_back(3, 30);
        initMap.emplace_back(4, 30);
        initMap.emplace_back(5, 30);
        initMap.emplace_back(6, 30);
        initMap.emplace_back(7, 30);
        initMap.emplace_back(8, 30);
        initMap.emplace_back(9, 30);
        initMap.emplace_back(10, 30);
        initMap.emplace_back(11, 30);
        initMap.emplace_back(12, 30);
        initMap.emplace_back(13, 30);
        initMap.emplace_back(14, 30);
        initMap.emplace_back(15, 30);
        initMap.emplace_back(16, 30);
        initMap.emplace_back(17, 30);
        initMap.emplace_back(18, 30);
        initMap.emplace_back(19, 30);
        initMap.emplace_back(20, 30);
        initMap.emplace_back(21, 30);
        initMap.emplace_back(22, 30);
        initMap.emplace_back(23, 30);
        initMap.emplace_back(24, 30);
        initMap.emplace_back(25, 30);
        initMap.emplace_back(26, 30);
        initMap.emplace_back(27, 30);
        initMap.emplace_back(28, 30);
        initMap.emplace_back(29, 30);
        initMap.emplace_back(30, 30);
    }
    void showMap() const;

private:
    std::vector<gs::Point> initMap;
};

} // namespace gs
