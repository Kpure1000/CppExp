#include "Array.h"
#include <iostream>

struct TestData
{
    int a = 0;
};

int main()
{
    Array<TestData, 5> data;
    for (auto it : data)
    {
        std::cout << it.a << " ";
    }
    std::cout << std::endl;
    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::cout << it->a << " ";
    }
    std::cout << std::endl;
}