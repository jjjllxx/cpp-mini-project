#include "Staff.h"
#include "Student.h"
#include <cstring>
#include <iostream>
#include <string>

int main()
{
    sims::StudentMIS sysu;

    sims::Staff::showStartMenu(true);
    std::string init;

    while (std::cin >> init)
    {
        if (init != "1" && init != "2")
        {
            sims::Staff::showStartMenu(false, true);
            continue;
        }

        if (init == "2")
        {
            break;
        }

        sims::Staff::showLoginMenu();
        std::string user;

        while (std::cin >> user)
        {
            if (user.size() != 1 || user[0] < '1' || user[0] > '4')
            {
                sims::Staff::showLoginMenu(true);

                continue;
            }

            if (user == "1")
            {
                sims::Staff::operateAsAdmissionsStaff(sysu);
            }
            else if (user == "2")
            {
                sims::Staff::operateAsRegistrar(sysu);
            }
            else if (user == "3")
            {
                sims::Staff::operateAsDegreeStaff(sysu);
            }
            else
            {
                break;
            }

            sims::Staff::showLoginMenu();
        }

        sims::Staff::showStartMenu();
    }

    return 0;
}