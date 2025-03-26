#pragma once
#include "Menu.h"
#include <string>
#include <vector>

namespace ssos
{
// 卖家有密码成员变量
class Seller
{
private:
    std::string password;

public:
    Seller();
    void        confirmOrders(std::vector<ssos::Order>& orders);
    void        inquireOrder(const std::vector<ssos::Order>& orders);
    void        appendMenu();
    void        cancelMenu(std::vector<ssos::Dish>& menu);
    void        setPassword(const std::string& pwd);
    std::string getPassword();
};
} // namespace ssos
