#include "utils/Vector.hpp"
#include <iostream>
int main()
{
    Vec2f a(1.0f, 2.0f);
    Vec2f b(2.0f, 3.0f);
    a += b;
    try
    {
        std::cout << a[1] << ", " << a[2] << std::endl;
    }
    catch (const char* e)
    {
        std::cerr << e << '\n';
    }
}