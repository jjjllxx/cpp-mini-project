#include <cstring>
#include <iostream>

#include "I18n.h"
#include "Interface.h"
#include "Scene.h"
#include "Utility.h"

static void printHelp()
{
    std::cout << '\n';
    std::cout << "sudoku - a little game in command line" << '\n'
              << '\n';
    std::cout << "Usage:" << '\n';
    std::cout << "\t sudoku [-l <progressFile>]" << '\n'
              << '\n';
    std::cout << "Options:" << '\n';
    std::cout << "\t -l <path> \t specify path of progress file to load, optional." << '\n'
              << '\n';
}

int main(int argc, char** argv)
{
    sdk::Scene scene;

    if (argc == 1)
    {
        sdk::Interface::inputLanguage();
        int eraseGridNumber = sdk::Interface::inputDifficulty();
        scene.generate();
        scene.eraseRandomGrids(eraseGridNumber);
    }
    else if (argc == 3 && (strcmp(argv[1], "-l") == 0)) // NOLINT
    {
        // load saved game progress
        if (scene.load(argv[2]) == false) // NOLINT
        {
            sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::LOAD_PROGRESS_FAIL));
            return 0;
        }
        sdk::Interface::inputLanguage();
    }
    else
    {
        printHelp();
        return 0;
    }

    scene.setMode(sdk::Interface::inputKeyMode());

    scene.play();

    return 0;
}