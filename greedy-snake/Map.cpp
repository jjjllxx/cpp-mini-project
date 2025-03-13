#include "Map.h"
#include "Point.h"
#include <unistd.h>

void gs::Map::showMap() const
{
    for (const gs::Point& pt : initMap)
    {
        pt.showSquare();
        usleep(10 * 1000);
    }
}
