#include "Seller.h"
#include "Interface.h"
#include "Menu.h"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

ssos::Seller::Seller() :
    password("888888")
{
}

void ssos::Seller::appendMenu()
{
    std::cout << '\n'
              << "Do you want to append Menu?  Y/N" << '\n';
    std::string             ch;
    std::vector<ssos::Dish> dishesToAdd;

    while (std::cin >> ch)
    {
        // 判断无效输入
        if (ch != "Y" && ch != "y")
        {
            break;
        }
        std::cout << '\n'
                  << "please input the dish name : ";
        ssos::Dish dish;
        std::cin >> dish.name;
        std::cout << '\n'
                  << "Please input the dish ID : ";
        std::cin >> dish.id;
        std::cout << '\n'
                  << "Please input the price of the dish : ";
        std::cin >> dish.price;
        dishesToAdd.push_back(dish);
        std::cout << '\n'
                  << "The dish have been added to the menu!" << '\n';
        std::cout << '\n'
                  << "Do you want to continue to append ssos::Menu? Y/N" << '\n';
    }

    ssos::Interface::writeMenuToFile(dishesToAdd, std::ios::app);
}

void ssos::Seller::cancelMenu(std::vector<ssos::Dish>& menu)
{
    std::cout << '\n'
              << "Do you want to cancel Menu? Y/N" << '\n';
    std::string str;
    std::string ch;

    while (std::cin >> ch)
    {
        std::vector<ssos::Dish>::iterator it = menu.begin();
        if (ch == "N" || ch == "n")
        {
            break;
        }
        // 判断无效输入
        if (ch != "Y" && ch != "y")
        {
            std::cout << '\n'
                      << "Invalid input!Please input again!" << '\n';
            std::cout << '\n'
                      << "Do you want to cancel Menu? Y/N" << '\n';
            continue;
        }

        ssos::Interface::showMenu(menu);

        std::cout << '\n'
                  << "Please input the dish ID you want cancel : ";
        std::cin >> str;
        for (std::size_t i = 0; i < menu.size(); ++i)
        {
            if (menu[i].id == str)
            {
                menu.erase(it + static_cast<long>(i));
                std::cout << '\n'
                          << "The dish have been canceled!" << '\n';
                break;
            }
            // 找不到该编号
            if (i == menu.size() - 1)
            {
                std::cout << '\n'
                          << "There is no such dish!Please input again!" << '\n';
            }
        }
        std::cout << '\n'
                  << "Do you want to continue to cancel Menu? Y/N" << '\n';
    }

    ssos::Interface::writeMenuToFile(menu, std::ios::out);
}

// 卖家查询订单
void ssos::Seller::inquireOrder(const std::vector<ssos::Order>& orders)
{
    ssos::Interface::showOrders(orders);
}

// 卖家确认订单
void ssos::Seller::confirmOrders(std::vector<ssos::Order>& orders)
{
    std::vector<std::size_t> ordersIdxToCancel;

    for (std::size_t i = 0; i < orders.size(); ++i)
    {
        if (orders[i].checkIfCanCancel() == true)
        {
            ordersIdxToCancel.push_back(i);
        }
    }

    if (ordersIdxToCancel.empty() == true)
    {
        std::cout << '\n'
                  << "All order have been confirmed!" << '\n';
        return;
    }
    std::cout << std::left;
    std::cout << '\n'
              << "Here is the order you haven't confirmed: " << '\n';
    std::cout << '\n'
              << std::setw(7) << "DishID" << std::setw(10) << "DishName"
              << std::setw(6) << "price" << std::setw(4) << "num" << std::setw(8)
              << "Name";
    std::cout << std::setw(8) << "Phone" << std::setw(12) << "Address"
              << std::setw(15) << "ssos::Date" << std::setw(10) << "state" << '\n';
    int cnt = 0;
    for (const std::size_t idx : ordersIdxToCancel)
    {
        cnt++;
        std::cout << cnt << '\n';
        ssos::Interface::printOrder(orders[idx]);
    }

    std::cout << std::right;
    std::cout << '\n'
              << std::setw(20) << "1.Aprove all" << std::setw(25)
              << "2.Aprove one by one" << std::setw(20) << "3.return" << '\n';
    std::string n;
    while (std::cin >> n)
    {
        if (n == "1" || n == "2" || n == "3")
        {
            break;
        }
        else
        {
            std::cout << '\n'
                      << "Invalid input!" << '\n';
            std::cout << '\n'
                      << std::setw(20) << "1.Aprove all" << std::setw(25)
                      << "2.Aprove one by one" << std::setw(20) << "3.return" << '\n';
        }
    }
    if (n == "3")
    {
        return;
    }
    if (n == "1")
    {
        for (const std::size_t idx : ordersIdxToCancel)
        {
            orders[idx].confirmOrder();
        }
    }
    else
    {
        std::cout << std::right;
        std::cout << '\n'
                  << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
                  << '\n';
        int opt = 0;
        while (std::cin >> opt)
        {
            if (opt == 2)
            {
                return;
            }

            if (opt != 1)
            {
                std::cout << '\n'
                          << "Invalid input!" << '\n';
                return;
            }
            std::cout << '\n'
                      << "Please input the number of order:";
            std::cin >> opt;

            if (opt > cnt)
            {
                std::cout << '\n'
                          << "There is only " << cnt << " order!" << '\n';
                std::cout << '\n'
                          << "Please input again!" << '\n';
            }
            else if (opt <= 0)
            {
                std::cout << '\n'
                          << "The number must be positive !" << '\n';
            }
            else
            {
                orders[ordersIdxToCancel[opt - 1]].confirmOrder();
                std::cout << '\n'
                          << "The order have approved!" << '\n';
            }
            std::cout << std::right;
            std::cout << '\n'
                      << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
                      << '\n';
        }
    }

    ssos::Interface::writeOrdersToFile(orders, std::ios::out);
}

void ssos::Seller::setPassword(const std::string& pwd)
{
    password = pwd;
}

std::string ssos::Seller::getPassword()
{
    return password;
}