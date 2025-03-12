#pragma once

#include "Menu.h"
#include "Seller.h"
#include <iomanip>
#include <vector>

namespace ssos
{
struct Dish;
class Order;
class Seller;

namespace Interface
{
    std::vector<ssos::Dish>  loadMenu();
    std::vector<ssos::Order> loadOrders();

    void showStartMenu(const bool hasErrorBefore = false);
    bool verifySellerPassword(ssos::Seller& seller);
    void showSellerOptions(const bool hasErrorBefore = false);
    void updateSellerPassword(ssos::Seller& seller);
    void showBuyerOptions(const bool hasErrorBefore = false);

    void operateAsSeller();
    void operateAsBuyer();

    void printOrder(const ssos::Order& order);
    void writeMenuToFile(const std::vector<ssos::Dish>& menu,
                         const std::ios_base::openmode& mode);
    void writeOrdersToFile(const std::vector<ssos::Order>& orders,
                           const std::ios_base::openmode&  mode);

    void showMenu(const std::vector<ssos::Dish>& menu);
    void showOrders(const std::vector<ssos::Order>& orders);
} // namespace Interface
} // namespace ssos