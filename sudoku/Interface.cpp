#include <iostream>
#include <string>

#include "Common.h"
#include "I18n.h"
#include "Interface.h"
#include "Utility.h"

// return number of grids to be erased
int sdk::Interface::inputDifficulty()
{
    sdk::Utility::cls();

    std::string cmd;
    int         gridsNumToErase = 0;
    while (true)
    {
        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::ASK_DIFFICULTY));

        std::cin >> cmd;

        try
        {
            switch (static_cast<sdk::Difficulty>(std::stoi(cmd)))
            {
            case sdk::Difficulty::EASY:
                gridsNumToErase = 20;
                break;
            case sdk::Difficulty::NORMAL:
                gridsNumToErase = 35;
                break;
            case sdk::Difficulty::HARD:
                gridsNumToErase = 50;
                break;
            }
        }
        catch (...)
        {
            gridsNumToErase = 0;
        }

        if (gridsNumToErase > 0)
        {
            break;
        }

        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::INPUT_ERROR));
    }

    return gridsNumToErase;
}

sdk::KeyMode sdk::Interface::inputKeyMode()
{
    std::string mode;
    while (true)
    {
        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::ASK_KEY_MAP));
        std::cin >> mode;

        try
        {
            return static_cast<sdk::KeyMode>(std::stoi(mode));
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Invalid argument: " << mode << " is not a number.\n";
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range: " << mode << " is too large or too small.\n";
        }

        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::INPUT_ERROR));
    }
}

void sdk::Interface::inputLanguage()
{
    std::string language;
    while (true)
    {
        sdk::Utility::message("1English 2中文");
        std::cin >> language;

        try
        {
            if (const sdk::Language lang = static_cast<sdk::Language>(std::stoul(language) - 1);
                lang < sdk::Language::MAX)
            {
                sdk::I18n::Instance().SetLanguage(lang);
                return;
            }
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << "Invalid argument: '" << language << "' is not a valid number.\n";
        }
        catch (const std::out_of_range& e)
        {
            std::cerr << "Out of range: '" << language << "' is too large.\n";
        }

        sdk::Utility::message(sdk::I18n::Instance().Get(sdk::Key::INPUT_ERROR));
    }
}
