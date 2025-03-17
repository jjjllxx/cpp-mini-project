#include "json.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

jp::Json::Json() :
    type(jp::Type::Null)
{
}

jp::Json::Json(const bool val) :
    type(jp::Type::Bool),
    value(val)
{
}

jp::Json::Json(const int val) :
    type(jp::Type::Int),
    value(val)
{
}

jp::Json::Json(const double val) :
    type(jp::Type::Double),
    value(val)
{
}

jp::Json::Json(const char* val) :
    type(jp::Type::String),
    value(new std::string(val))
{
}

jp::Json::Json(const std::string& val) :
    type(jp::Type::String),
    value(new std::string(val))
{
}

jp::Json::Json(const Type type) :
    type(type)
{
    switch (type)
    {
    case jp::Type::Null:
        break;
    case jp::Type::Bool:
        this->value = false;
        break;
    case jp::Type::Int:
        this->value = 0;
        break;
    case jp::Type::Double:
        this->value = 0.0;
        break;
    case jp::Type::String:
        this->value = new std::string("");
        break;
    case jp::Type::Array:
        this->value = new std::vector<jp::Json>();
        break;
    case jp::Type::Object:
        this->value = new std::map<std::string, jp::Json>();
        break;
    default:
        break;
    }
}

jp::Json::Json(const jp::Json& json)
{
    jp::Json::clear();
    jp::Json::copy(json);
}

jp::Json::operator bool()
{
    if (this->type != jp::Type::Bool)
    {
        throw new std::logic_error("Type error, not bool type!");
    }

    return std::get<bool>(this->value);
}

jp::Json::operator int()
{
    if (this->type != jp::Type::Int)
    {
        throw new std::logic_error("Type error, not int type!");
    }

    return std::get<int>(this->value);
}

jp::Json::operator double()
{
    if (this->type != jp::Type::Double)
    {
        throw new std::logic_error("Type error, not double type!");
    }

    return std::get<double>(this->value);
}

jp::Json::operator std::string()
{
    if (this->type != jp::Type::String)
    {
        throw new std::logic_error("Type error, not string type!");
    }

    return *std::get<std::string*>(this->value);
}

jp::Json& jp::Json::operator[](const int idx)
{
    if (idx < 0)
    {
        throw new std::logic_error("Invalid Index");
    }

    if (this->type != jp::Type::Array)
    {
        this->clear();
        this->type  = jp::Type::Array;
        this->value = new std::vector<jp::Json>();
    }

    while (static_cast<int>((std::get<std::vector<jp::Json>*>(this->value))->size()) <= idx)
    {
        std::get<std::vector<jp::Json>*>(this->value)->push_back(Json());
    }

    return (std::get<std::vector<jp::Json>*>(this->value))->at(idx);
}

jp::Json& jp::Json::operator[](const char* key)
{
    return jp::Json::operator[](std::string(key));
}

jp::Json& jp::Json::operator[](const std::string& key)
{
    if (this->type != jp::Type::Object)
    {
        this->clear();
        this->type = jp::Type::Object;

        this->value = new std::map<std::string, jp::Json>();
    }

    if (std::get<std::map<std::string, jp::Json>*>(this->value)->find(key) == std::get<std::map<std::string, jp::Json>*>(this->value)->end())
    {
        std::get<std::map<std::string, jp::Json>*>(this->value)->insert({ key, Json() });
    }

    return std::get<std::map<std::string, jp::Json>*>(this->value)->at(key);
}

jp::Json& jp::Json::operator=(const jp::Json& json)
{
    jp::Json::clear();
    jp::Json::copy(json);

    return *this;
}

bool jp::Json::operator==(const jp::Json& other) const
{
    if (this->type != other.type)
    {
        return false;
    }

    switch (this->type)
    {
    case jp::Type::Null:
        return true;
    case jp::Type::Bool:
        return std::get<bool>(this->value) == std::get<bool>(other.value);
    case jp::Type::Int:
        return std::get<int>(this->value) == std::get<int>(other.value);
    case jp::Type::Double:
        return std::get<double>(this->value) == std::get<double>(other.value);
    case jp::Type::String:
        return std::get<std::string*>(this->value) == std::get<std::string*>(other.value);
    case jp::Type::Array:
        return std::get<std::vector<jp::Json>*>(this->value)
               == std::get<std::vector<jp::Json>*>(other.value);
    case jp::Type::Object:
        return std::get<std::map<std::string, jp::Json>*>(this->value)
               == std::get<std::map<std::string, jp::Json>*>(other.value);
    default:
        break;
    }
}

bool jp::Json::operator!=(const jp::Json& other) const
{
    return !jp::Json::operator==(other);
}

void jp::Json::append(const Json& json)
{
    if (this->type != jp::Type::Array)
    {
        this->type  = jp::Type::Array;
        this->value = new std::vector<jp::Json>();
    }

    (std::get<std::vector<jp::Json>*>(this->value))->push_back(json);
}

std::string jp::Json::str() const
{
    std::stringstream ss;
    switch (this->type)
    {
    case jp::Type::Null:
        ss << "null";
        break;
    case jp::Type::Bool:
        std::get<bool>(this->value) == true
            ? ss << "true"
            : ss << "false";
        break;
    case jp::Type::Int:
        ss << std::get<int>(this->value);
        break;
    case jp::Type::Double:
        ss << std::get<double>(this->value);
        break;
    case jp::Type::String:
        ss << '\"' << *std::get<std::string*>(this->value) << '\"';
        break;
    case jp::Type::Array:
    {
        ss << '[';
        for (auto it = std::get<std::vector<jp::Json>*>(this->value)->begin();
             it != std::get<std::vector<jp::Json>*>(this->value)->end();
             ++it)
        {
            if (it != std::get<std::vector<jp::Json>*>(this->value)->begin())
            {
                ss << ", ";
            }
            ss << it->str();
        }
        ss << ']';
        break;
    }

    case jp::Type::Object:
    {
        ss << '{';
        for (auto it = std::get<std::map<std::string, jp::Json>*>(this->value)->begin();
             it != std::get<std::map<std::string, jp::Json>*>(this->value)->end();
             ++it)
        {
            if (it != std::get<std::map<std::string, jp::Json>*>(this->value)->begin())
            {
                ss << ", ";
            }

            ss << '\"' << it->first << '\"' << ": " << it->second.str();
        }
        ss << '}';
        break;
    }

    default:
        break;
    }

    return ss.str();
}

void jp::Json::clear()
{
    switch (this->type)
    {
    case jp::Type::Null:
        break;
    case jp::Type::Bool:
        std::get<bool>(this->value) = false;
        break;
    case jp::Type::Int:
        std::get<int>(this->value) = 0;
        break;
    case jp::Type::Double:
        std::get<double>(this->value) = 0.0;
        break;
    case jp::Type::String:
        delete std::get<std::string*>(this->value);
        break;
    case jp::Type::Array:
    {
        for (jp::Json& json : *std::get<std::vector<jp::Json>*>(this->value))
        {
            json.clear();
        }
        delete std::get<std::vector<jp::Json>*>(this->value);
        break;
    }

    case jp::Type::Object:
        for (auto& [k, v] : *std::get<std::map<std::string, jp::Json>*>(this->value))
        {
            v.clear();
        }
        delete std::get<std::map<std::string, jp::Json>*>(this->value);
        break;
    default:
        break;
    }

    this->type = jp::Type::Null;
}

void jp::Json::copy(const jp::Json& json)
{
    this->type = json.type;
    switch (json.type)
    {
    case jp::Type::Null:
        break;
    case jp::Type::Bool:
        this->value = std::get<bool>(json.value);
        break;
    case jp::Type::Int:
        this->value = std::get<int>(json.value);
        break;
    case jp::Type::Double:
        this->value = std::get<double>(json.value);
        break;
    case jp::Type::String:
        this->value = std::get<std::string*>(json.value);
        break;
    case jp::Type::Array:
        this->value = std::get<std::vector<jp::Json>*>(json.value);
        break;
    case jp::Type::Object:
        this->value = std::get<std::map<std::string, jp::Json>*>(json.value);
        break;
    default:
        break;
    }
}

bool jp::Json::asBool() const
{
    if (this->type != jp::Type::Bool)
    {
        throw new std::logic_error("Type error, not bool type!");
    }

    return std::get<bool>(this->value);
}
int jp::Json::asInt() const
{
    if (this->type != jp::Type::Int)
    {
        throw new std::logic_error("Type error, not int type!");
    }

    return std::get<int>(this->value);
}

double jp::Json::asDouble() const
{
    if (this->type != jp::Type::Double)
    {
        throw new std::logic_error("Type error, not double type!");
    }

    return std::get<double>(this->value);
}

std::string jp::Json::asString() const
{
    if (this->type != jp::Type::String)
    {
        throw new std::logic_error("Type error, not string type!");
    }

    return *std::get<std::string*>(this->value);
}

bool jp::Json::has(const int idx) const
{
    if (this->type != jp::Type::Array)
    {
        throw new std::logic_error("Type error, not array type!");
    }

    return idx >= 0
           && static_cast<int>(std::get<std::vector<jp::Json>*>(this->value)->size()) > idx;
}

bool jp::Json::has(const std::string& key) const
{
    if (this->type != jp::Type::Object)
    {
        throw new std::logic_error("Type error, not object type!");
    }

    return (std::get<std::map<std::string, jp::Json>*>(this->value))->find(key)
           != (std::get<std::map<std::string, jp::Json>*>(this->value))->end();
}

bool jp::Json::has(const char* key) const
{
    return jp::Json::has(std::string(key));
}

void jp::Json::remove(const int idx)
{
    if (jp::Json::has(idx) == true)
    {
        std::get<std::vector<jp::Json>*>(this->value)->at(idx).clear();
        std::cout << this->str() << std::endl;
        std::get<std::vector<jp::Json>*>(this->value)
            ->erase(std::next(std::get<std::vector<jp::Json>*>(this->value)->begin(), idx));
    }
}

void jp::Json::remove(const std::string& key)
{
    if (jp::Json::has(key) == true)
    {
        std::get<std::map<std::string, jp::Json>*>(this->value)->at(key).clear();
        std::get<std::map<std::string, jp::Json>*>(this->value)->erase(key);
    }
}

void jp::Json::remove(const char* key)
{
    jp::Json::remove(std::string(key));
}