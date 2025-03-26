#include "Buyer.h"
#include "Interface.h"
#include "Menu.h"
#include <cmath>
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

ssos::Buyer::Buyer() :
    name("no"), address("no")
{
}

void ssos::Buyer::createOrder(const std::vector<ssos::Dish>& menu)
{
    if (menu.empty() == true)
    {
        std::cout << '\n'
                  << "Sorry! There is no dish for you to choose!" << '\n';
        return;
    }

    ssos::Interface::showMenu(menu);

    std::cout << std::right;
    std::cout << '\n'
              << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
              << '\n';

    std::string              str;
    std::vector<ssos::Order> newOrders;

    while (std::cin >> str)
    {
        if (str == "2")
        {
            break;
        }
        std::cout << "Please input the dish ID : ";
        std::cin >> str;

        bool canFind = false;
        for (const ssos::Dish& dish : menu)
        {
            if (dish.id == str)
            {
                newOrders.emplace_back(dish);
                canFind = true;
                break;
            }
        }

        if (canFind == false)
        {
            std::cout << '\n'
                      << "There is no such dish!" << '\n';
            std::cout << '\n'
                      << std::setw(30) << "1.Continue" << std::setw(20)
                      << "2.return" << '\n';
            canFind = false;
            continue;
        }

        int m = 0;
        std::cout << '\n'
                  << "Please input the count you want : ";
        std::cin >> m;
        newOrders.back().setAmount(m);
        std::cout << '\n'
                  << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
                  << '\n';
    }

    ssos::Interface::showOrders(newOrders);

    if (name == "no" || address == "no")
    {
        std::cout << '\n'
                  << "Please input your name : ";
        std::cin >> name;
        std::cout << '\n'
                  << "Please input your address : ";
        std::cin >> address;
        std::cout << '\n'
                  << "Please input your phone : ";
        std::cin >> phone;
    }

    char ch = 0;
    std::cout << '\n'
              << "Please input the date you want to have you dish," << '\n';
    std::cout << "just as 2013/5/2 14 (year/month/day hour) : " << '\n';
    std::cin >> bookDate.year >> ch >> bookDate.month >> ch >> bookDate.day >> bookDate.hour;

    for (ssos::Order& newOrder : newOrders)
    {
        newOrder.setCustomerName(name);
        newOrder.setAddress(address);
        newOrder.setPhone(phone);
        newOrder.setBookDate(bookDate);
    }

    this->buyerOrders.insert(buyerOrders.end(), newOrders.begin(), newOrders.end());

    
        ssos::Interface::writeOrdersToFile(newOrders, std::ios::app);
}

void ssos::Buyer::inquireOrders(const std::vector<ssos::Order>& orders)
{
    if (name == "no")
    {
        std::cout << '\n'
                  << "please input your name : ";
        std::cin >> name;
    }
    this->buyerOrders.clear();
    for (const ssos::Order& order : orders)
    {
        if (order.getCustomerName() == name)
        {
            this->buyerOrders.push_back(order);
        }
    }

    ssos::Interface::showOrders(this->buyerOrders);
}

void ssos::Buyer::cancelOrders(const std::vector<ssos::Order>& orders)
{
    ssos::Interface::showOrders(this->buyerOrders);

    // 选择1-继续或2-返回上一层
    std::cout << std::right;
    std::cout << '\n'
              << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
              << '\n';

    std::string str;

    std::vector<bool> buyerOrdersToCancel(this->buyerOrders.size(), false);

    while (std::cin >> str)
    {
        if (str == "2")
        {
            break;
        }
        // 判断无效输入
        if (str != "1")
        {
            std::cout << '\n'
                      << "Invalid input!" << '\n';
            std::cout << '\n'
                      << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
                      << '\n';
            continue;
        }
        std::cout << '\n'
                  << "Please input the dishID : ";
        std::cin >> str;
        bool canFindDish = false;

        for (std::size_t i = 0; i < this->buyerOrders.size(); ++i)
        {
            if (this->buyerOrders[i].getDishID() == str)
            {
                // 该订单是否已确认
                if (this->buyerOrders[i].checkIfCanCancel() == true)
                {
                    std::cout << '\n'
                              << "The order have been canceled!" << '\n';

                    buyerOrdersToCancel[i] = true;
                    break;
                }
                else
                {
                    std::cout << '\n'
                              << "The order have been approved! You can't cancel it !"
                              << '\n';
                    break;
                }

                canFindDish = true;
            }
        }
        // 查看该买家想取消的编号是否存在
        if (canFindDish == false)
        {
            std::cout << '\n'
                      << "There is no such dish you have ordered!" << '\n';
        }

        std::cout << std::right;
        std::cout << '\n'
                  << std::setw(30) << "1.Continue" << std::setw(20) << "2.return"
                  << '\n';
    }

    std::vector<ssos::Order> ordersToKeep;

    for (const ssos::Order& order : orders)
    {
        bool needCancel = false;
        for (std::size_t i = 0; i < buyerOrders.size(); ++i)
        {
            if (buyerOrdersToCancel[i] == true && order.isSameWith(this->buyerOrders[i]) == true)
            {
                needCancel = true;
                break;
            }
        }

        if (needCancel == false)
        {
            ordersToKeep.push_back(order);
        }
    }

    ssos::Interface::writeOrdersToFile(ordersToKeep, std::ios::out);
}