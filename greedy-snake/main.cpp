#include "Controller.h"
#include "Utils.h"


int main()
{
    gs::Utils::initConsole();

    gs::Controller c;
    c.gameLoop();
    
    gs::Utils::endConsole();

    return 0;
}