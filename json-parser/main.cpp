#include <iostream>

#include "json/json.h"

bool isTrue(){
return true;
}

int main()
{
    jp::Json obj;

    obj["bool"]   = true;
    obj["int"]    = 42;
    obj["double"] = 3.14;
    obj["string"] = "hello";

    // std::cout << obj.has("bool") << std::endl;
    // std::cout << obj.has("Bool") << std::endl;
    // obj.remove("bool");
    // std::cout << obj.has("bool") << std::endl;

    // std::cout << obj.str() << std::endl;

    jp::Json arr;
    arr[0] = true;
    arr[1] = "test1";
    arr[2] = "true";
    arr[3] = 123;
    arr[4] = 1.23;
    arr[5] = obj;

    std::cout << arr.str() << std::endl;
    std::cout << arr[1].str() << std::endl;
    arr.remove(0);
    std::cout << arr[0].str() << std::endl;
    std::cout << arr.str() << std::endl;

    return 0;
}