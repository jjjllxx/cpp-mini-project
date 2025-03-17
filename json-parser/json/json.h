#pragma once

#include <map>
#include <string>
#include <vector>

namespace jp
{
enum class Type
{
    Null = 0,
    Bool,
    Int,
    Double,
    String,
    Array,
    Object,
};

class Json
{
public:
    Json();
    Json(const bool val);
    Json(const int val);
    Json(const double val);
    Json(const char* val);
    Json(const std::string& val);
    Json(const Type type);
    Json(const jp::Json& json);

    operator bool();
    operator int();
    operator double();
    operator std::string();

    jp::Json& operator[](const int idx);
    jp::Json& operator[](const char* key);
    jp::Json& operator[](const std::string& key);
    jp::Json& operator=(const jp::Json& json);

    bool operator==(const jp::Json& other) const;
    bool operator!=(const jp::Json& other) const;

    void        append(const jp::Json& json);
    std::string str() const;
    void        clear();

    std::vector<jp::Json>::iterator begin()
    {
        return std::get<std::vector<jp::Json>*>(this->value)->begin();
    }

    std::vector<jp::Json>::iterator end()
    {
        return std::get<std::vector<jp::Json>*>(this->value)->end();
    }

    bool isNull() const
    {
        return this->type == jp::Type::Null;
    }
    bool isInt() const
    {
        return this->type == jp::Type::Int;
    }
    bool isDouble() const
    {
        return this->type == jp::Type::Double;
    }
    bool isString() const
    {
        return this->type == jp::Type::String;
    }
    bool isArray() const
    {
        return this->type == jp::Type::Array;
    }
    bool isObject() const
    {
        return this->type == jp::Type::Object;
    }

    bool        asBool() const;
    int         asInt() const;
    double      asDouble() const;
    std::string asString() const;

    bool has(const int idx) const;
    bool has(const std::string& key) const;
    bool has(const char* key) const;

    void remove(const int idx);
    void remove(const std::string& key);
    void remove(const char* key);

private:
    jp::Type type;

    std::variant<bool, int, double, std::string*, std::vector<jp::Json>*, std::map<std::string, jp::Json>*> value;

    void copy(const jp::Json& json);
};
} // namespace jp
