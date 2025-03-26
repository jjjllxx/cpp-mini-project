#include "Menu.h"
#include <cstring>
#include <string>

ssos::Date::Date(const int y,
                 const int m,
                 const int d,
                 const int h) :
    year(y),
    month(m), day(d), hour(h)
{
}

bool ssos::Date::operator==(const ssos::Date& other) const
{
    return other.year == year && other.month == month && other.day == day && other.hour == hour;
}

ssos::Dish::Dish(const std::string& name,
                 const std::string& id,
                 const double       price) :
    price(price),
    id(id), name(name)
{
}

ssos::Order::Order(const ssos::Dish&  dish,
                   const std::string& customerName,
                   const std::string& address,
                   const std::string& phone,
                   const ssos::Date&  date) :
    customerName(customerName),
    address(address),
    phone(phone),
    bookDate(date),
    dish(dish)
{
}

ssos::Order::Order(const ssos::Dish& dish) :
    dish(dish)
{
}

bool ssos::Order::isSameWith(const ssos::Order& other) const
{
    return other.dish.id == this->dish.id && other.dish.name == this->dish.name && other.customerName == this->customerName
           && other.phone == this->phone && other.address == this->address && other.bookDate == this->bookDate;
}

std::string ssos::Order::getCustomerName() const
{
    return customerName;
}

std::string ssos::Order::getAdress() const
{
    return address;
}

std::string ssos::Order::getPhone() const
{
    return phone;
}

ssos::Date ssos::Order::getBookDate() const
{
    return bookDate;
}

bool ssos::Order::checkIfCanCancel() const
{
    return canCancel;
}

int ssos::Order::getAmount() const
{
    return amount;
}

std::string ssos::Order::getDishID() const
{
    return this->dish.id;
}

std::string ssos::Order::getDishName() const
{
    return this->dish.name;
}

double ssos::Order::getDishPrice() const
{
    return this->dish.price;
}

bool ssos::Order::setCustomerName(const std::string& customerName)
{
    if (this->canCancel == false)
    {
        return false;
    }
    this->customerName = customerName;
    return true;
}

bool ssos::Order::setAddress(const std::string& address)
{
    if (this->canCancel == false)
    {
        return false;
    }
    this->address = address;
    return true;
}

bool ssos::Order::setPhone(const std::string& phone)
{
    if (this->canCancel == false)
    {
        return false;
    }
    this->phone = phone;
    return true;
}

void ssos::Order::confirmOrder()
{
    canCancel = false;
}

bool ssos::Order::setBookDate(const ssos::Date& bookDate)
{
    if (this->canCancel == false)
    {
        return false;
    }
    this->bookDate = bookDate;
    return true;
}

bool ssos::Order::setAmount(const int amount)
{
    if (this->canCancel == false)
    {
        return false;
    }
    this->amount = amount;
    return true;
}