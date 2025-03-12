#pragma once
#include "Menu.h"
#include <string>
#include <vector>

namespace ssos
{
// 买家有名字、地址、电话、订单日期、自己的订单数量 和一个
// std::vector<ssos::Order>类型的用于存储买家自己的所有订单
class Buyer
{
private:
    std::vector<ssos::Order> buyerOrders;

    std::string name;
    std::string address;
    std::string phone;
    ssos::Date  bookDate;

public:
    Buyer();
    void createOrder(const std::vector<ssos::Dish>& menu);
    void cancelOrders(const std::vector<ssos::Order>& orders);
    void inquireOrders(const std::vector<ssos::Order>& orders);
};
} // namespace ssos
