
#pragma once
#include <string>

namespace ssos
{
struct Date
{
    Date() = default;
    Date(const int y,
         const int m,
         const int d,
         const int h);
    bool operator==(const ssos::Date& other) const;

    int year  = 12;
    int month = 12;
    int day   = 12;
    int hour  = 12;
};

struct Dish
{
    Dish() = default;
    Dish(const std::string& name,
         const std::string& id,
         const double       price);

    double price = 0.0;

    std::string id;
    std::string name;
};

// Order类存有用户名，地址，电话，数量，日期，确认状态
class Order
{
private:
    std::string customerName;
    std::string address;
    std::string phone;

    int        amount = 0;
    bool       canCancel = true;
    ssos::Date bookDate;
    ssos::Dish dish;

public:
    Order() = default;
    Order(const Dish&        dish,
          const std::string& customerName,
          const std::string& address,
          const std::string& phone,
          const ssos::Date&  date);
    Order(const Dish& dish);

    bool        isSameWith(const ssos::Order& other) const;
    std::string getCustomerName() const;
    std::string getAdress() const;
    std::string getPhone() const;
    ssos::Date  getBookDate() const;
    std::string getDishID() const;
    std::string getDishName() const;

    double getDishPrice() const;

    bool checkIfCanCancel() const;
    int  getAmount() const;
    bool setCustomerName(const std::string& customerName);
    bool setAddress(const std::string& address);
    bool setPhone(const std::string& phone);
    bool setAmount(const int amount);
    bool setBookDate(const ssos::Date& bookDate);
    void confirmOrder();
};
} // namespace ssos
