#include "Interface.h"
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>

int main()
{
    std::cout << std::setw(55) << "Welcome to the booking system!" << '\n';
    std::cout
        << "          ----------------------------------------------------------"
        << '\n';
    ssos::Interface::showStartMenu();

    std::string opt;
    while (std::cin >> opt)
    {
        if (opt == "3")
        {
            break;
        }

        if (opt != "1" && opt != "2")
        {
            ssos::Interface::showStartMenu(true);
            continue;
        }

        opt == "1"
            ? ssos::Interface::operateAsBuyer()
            : ssos::Interface::operateAsSeller();
        ssos::Interface::showStartMenu();
    }

    return 0;
}