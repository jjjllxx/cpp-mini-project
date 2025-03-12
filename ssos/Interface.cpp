
#include "Interface.h"
#include "Buyer.h"
#include "Menu.h"
#include "Seller.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<ssos::Order> orders;
std::vector<ssos::Dish>  dishes;

void ssos::Interface::showStartMenu(const bool hasErrorBefore)
{
    hasErrorBefore == true
        ? std::cout << '\n'
                    << "Invalid number!Please input again :" << '\n'
        : std::cout << std::right;
        
    std::cout << '\n'
              << std::setw(25) << "1.Buyer" << std::setw(15) << "2.Seller"
              << std::setw(15) << "3.Exit" << '\n';
}

// 用于读取文件中的菜单
std::vector<ssos::Dish> ssos::Interface::loadMenu()
{
    std::fstream finout;
    finout.open("menu.txt", std::ios::in);
    if (finout.fail())
    {
        std::cout << '\n'
                  << "The system can't find the file!" << '\n';
        return {};
    }

    std::vector<ssos::Dish> menu;

    while (!finout.eof())
    {
        ssos::Dish dish;

        finout >> dish.id;
        if (dish.id == " " || dish.id == "\n")
        {
            continue;
        }

        finout >> dish.name >> dish.price;
        if (dish.price < 0 || dish.price > 100000)
        {
            continue;
        }

        dishes.push_back(dish);
    }
    finout.close();

    return menu;
}

// 用于读取文件中的订单
std::vector<ssos::Order> ssos::Interface::loadOrders()
{
    std::fstream finout;
    finout.open("order.txt", std::ios::in);
    if (finout.fail())
    {
        std::cout << '\n'
                  << "The system can't find the file!" << '\n';
        return {};
    }

    while (!finout.eof())
    {
        ssos::Dish dish;
        finout >> dish.id;
        if (dish.id == " " || dish.id == "\n")
        {
            continue;
        }

        int         num = 0;
        std::string address;
        std::string phone;
        std::string name;

        finout >> dish.name >> dish.price >> num >> name >> address >> phone;
        if (dish.price < 0 || dish.price > 100000)
        {
            continue;
        }

        int        modify = 0;
        ssos::Date date;

        finout >> date.year >> date.month >> date.day >> date.hour >> modify;
        ssos::Order order(dish, name, address, phone, date);
        order.setAmount(num);

        if (modify == 0)
        {
            order.confirmOrder();
        }

        orders.push_back(order);
    }

    return orders;
}

void ssos::Interface::printOrder(const ssos::Order& order)
{
    std::cout << std::left;
    std::cout << std::setw(7) << order.getDishID() << std::setw(10)
              << order.getDishName() << std::setw(6) << order.getDishPrice()
              << std::setw(4) << order.getAmount();
    std::cout << std::setw(8) << order.getCustomerName() << std::setw(8)
              << order.getPhone() << std::setw(12) << order.getAdress();
    std::cout << " ";

    std::cout << std::left;
    std::cout << order.getBookDate().year << '/' << order.getBookDate().month << '/' << order.getBookDate().day << "-"
              << order.getBookDate().hour << 'h';
    std::cout << "  ";
    if (order.checkIfCanCancel() == true)
    {
        std::cout << std::setw(10) << "New" << '\n';
    }
    else
    {
        std::cout << std::setw(10) << "Approved" << '\n';
    }
}

void ssos::Interface::writeMenuToFile(const std::vector<ssos::Dish>& menu,
                                      const std::ios_base::openmode& mode)
{
    std::fstream finout;
    finout.open("menu.txt", mode);
    if (finout.fail())
    {
        std::cout << '\n'
                  << "The system can't find the file!" << '\n';
        return;
    }

    for (const ssos::Dish& dish : menu)
    {
        finout << dish.id << ' ' << dish.name << ' '
               << dish.price << '\n';
    }

    finout.close();
}

void ssos::Interface::writeOrdersToFile(const std::vector<ssos::Order>& orders,
                                        const std::ios_base::openmode&  mode)
{
    std::fstream finout;
    finout.open("order.txt", mode);
    if (finout.fail())
    {
        std::cout << '\n'
                  << "The system can't find the file!" << '\n';
        return;
    }

    for (const ssos::Order& order : orders)
    {
        ssos::Date date   = order.getBookDate();
        int        modify = order.checkIfCanCancel() ? 1 : 0;
        finout << order.getDishID() << ' ' << order.getDishName() << ' '
               << order.getDishPrice() << ' ' << order.getAmount() << '\n';
        finout << order.getCustomerName() << ' ' << order.getAdress() << ' '
               << order.getPhone() << '\n';
        finout << date.year << ' ' << date.month << ' ' << date.day << ' ' << date.hour
               << ' ' << modify << '\n';
    }

    finout.close();
}

bool ssos::Interface::verifySellerPassword(ssos::Seller& seller)
{
    std::string pwd;

    std::fstream finout;
    finout.open("password.txt", std::ios::in);
    if (finout.fail())
    {
        std::cout << '\n'
                  << "The system can't find the file!" << '\n';
        return false;
    }
    finout >> pwd;
    finout.close();

    seller.setPassword(pwd);
    std::cout << '\n'
              << "Please input your password ( default is 888888 ) :";
    std::string str;
    int         maxTrial = 5;
    std::cin >> str;

    while (maxTrial-- != 0 && str != pwd)
    {
        std::cout << '\n'
                  << "The password is wrong!\nPlease input again : ";
        std::cin >> str;
    }

    if (maxTrial <= 0)
    {
        std::cout << '\n'
                  << "You have input wrong password five times!" << '\n';
        return false;
    }

    return true;
}

void ssos::Interface::showSellerOptions(const bool hasErrorBefore)
{
    // 1为增加菜单，2为删除菜单，3为查询订单，4为确认订单，5为设置密码，6返回主菜单
    hasErrorBefore == true
        ? std::cout << '\n'
                    << "Invalid input!Please input anain!" << '\n'
        : std::cout << '\n'
                    << "Please choose the function you want :" << '\n';
    std::cout << std::left;
    std::cout << '\n'
              << "           " << std::setw(30) << "1. Append menu"
              << std::setw(20) << "2. Cancel menu" << '\n';
    std::cout << "           " << std::setw(30) << "3. Inquire" << std::setw(20)
              << "4.Modify" << '\n';
    std::cout << "           " << std::setw(30) << "5.Set password"
              << std::setw(20) << "6.Main Menu" << '\n';
}

void ssos::Interface::updateSellerPassword(ssos::Seller& seller)
{
    std::string str1;
    std::string str2;
    std::cout << std::right;
    std::cout << '\n'
              << std::setw(35) << "1.Continue" << std::setw(20) << "2.return"
              << '\n';

    while (std::cin >> str1)
    {
        if (str1 == "2")
        {
            break;
        }

        if (str1 != "1")
        {
            std::cout << "Invalid input!" << '\n';
            std::cout << '\n'
                      << std::setw(35) << "1.Continue" << std::setw(20)
                      << "2.return" << '\n';
            continue;
        }
        std::cout << "Please input your old password : ";
        std::cin >> str1;
        if (str1 == seller.getPassword())
        {
            break;
        }
        else
        {
            std::cout << std::right;
            std::cout << '\n'
                      << "Wrong!" << '\n';
            std::cout << '\n'
                      << std::setw(35) << "1.Continue" << std::setw(20)
                      << "2.return" << '\n';
        }
    }

    if (str1 == "2")
    {
        ssos::Interface::showSellerOptions();
        return;
    }

    std::cout << '\n'
              << "Please input your new password : ";
    std::cin >> str1;
    std::cout << '\n'
              << "Please input again :";
    std::cin >> str2;

    if (str1 == str2)
    {
        std::fstream finout;
        finout.open("password.txt", std::ios::out);
        if (finout.fail())
        {
            std::cout << '\n'
                      << "The system can't find the file!" << '\n';
            return;
        }
        finout << str1;
        finout.close();
        seller.setPassword(str1);
        std::cout << '\n'
                  << "The new password have benn set!" << '\n';
    }
    else
    {
        std::cout
            << '\n'
            << "The new password you have input twice times is different!"
            << '\n';
    }
}

void ssos::Interface::operateAsSeller()
{
    ssos::Seller seller;

    if (ssos::Interface::verifySellerPassword(seller) == false)
    {
        return;
    }
    ssos::Interface::showSellerOptions();

    std::string opt;
    while (std::cin >> opt)
    {
        if (opt == "6")
        {
            break;
        }

        if (opt.size() != 1 || opt[0] < '1' || opt[0] > '5')
        {
            ssos::Interface::showSellerOptions(true);
            continue;
        }

        if (orders = ssos::Interface::loadOrders();
            orders.empty() == true)
        {
            break;
        }

        if (dishes = ssos::Interface::loadMenu();
            dishes.empty() == true)
        {
            break;
        }

        if (opt == "1")
        {
            seller.appendMenu();
        }
        else if (opt == "2")
        {
            seller.cancelMenu(dishes);
        }
        else if (opt == "3")
        {
            seller.inquireOrder(orders);
        }
        else if (opt == "4")
        {
            seller.confirmOrders(orders);
        }
        else
        {
            ssos::Interface::updateSellerPassword(seller);
        }

        ssos::Interface::showSellerOptions();
    }
}

void ssos::Interface::showBuyerOptions(const bool hasErrorBefore)
{
    // 1为点菜，2为查询订单，3为修改订单 ，4返回主菜单
    std::cout << std::left;
    hasErrorBefore == true
        ? std::cout << '\n'
                    << "Invalid input!Please input anain!" << '\n'
        : std::cout << '\n'
                    << "Please continue to choose the function you want:" << '\n';
    std::cout << '\n'
              << "           " << std::setw(20) << "1. Order" << std::setw(20)
              << "2. Inquire" << '\n';
    std::cout << "           " << std::setw(20) << "3. Cancel" << std::setw(20)
              << "4.Main Menu" << '\n';
}

void ssos::Interface::operateAsBuyer()
{
    ssos::Buyer buyer;
    ssos::Interface::showBuyerOptions();

    std::string opt;
    std::cin >> opt;

    while (std::cin >> opt)
    {
        if (opt == "4")
        {
            return;
        }
        if (opt != "1" && opt != "2" && opt != "3")
        {
            ssos::Interface::showBuyerOptions(true);
            continue;
        }

        if (orders = ssos::Interface::loadOrders();
            orders.empty() == true)
        {
            break;
        }

        if (dishes = ssos::Interface::loadMenu();
            dishes.empty() == true)
        {
            break;
        }
        if (opt == "1")
        {
            buyer.createOrder(dishes);
        }
        else if (opt == "2")
        {
            buyer.inquireOrders(orders);
        }
        else if (opt == "3")
        {
            buyer.cancelOrders(orders);
        }

        ssos::Interface::showBuyerOptions();
    }
}

void ssos::Interface::showMenu(const std::vector<ssos::Dish>& menu)
{
    std::cout << std::left;
    std::cout << '\n'
              << "Here is the Menu :" << '\n';
    std::cout << '\n'
              << "        " << std::setw(20) << "DishID" << std::setw(20)
              << "DishName" << std::setw(20) << "Price" << '\n';
    for (const ssos::Dish& dish : menu)
    {
        std::cout << "        ";
        std::cout << std::left;
        std::cout << std::setw(20) << dish.id << std::setw(20)
                  << dish.name << std::setw(20) << dish.price << '\n';
    }
}

void ssos::Interface::showOrders(const std::vector<ssos::Order>& buyerOrders)
{
    if (buyerOrders.empty() == true)
    {
        std::cout << '\n'
                  << "No orders that meet the requirement." << '\n';
        return;
    }
    std::cout << std::left;
    std::cout << '\n'
              << "Here are the orders that meet the requirement:" << '\n';
    std::cout << '\n'
              << std::setw(7) << "DishID" << std::setw(10) << "DishName"
              << std::setw(6) << "price" << std::setw(4) << "num" << std::setw(8)
              << "Name";
    std::cout << std::setw(8) << "Phone" << std::setw(12) << "Address"
              << std::setw(15) << "Date" << std::setw(10) << "state" << '\n';

    int cnt = 0;
    for (const ssos::Order& myOrder : buyerOrders)
    {
        cnt++;
        std::cout << cnt << '\n';
        ssos::Interface::printOrder(myOrder);
    }
}
