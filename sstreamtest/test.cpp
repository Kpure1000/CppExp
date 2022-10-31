#include <sstream>
#include <iostream>
#include <iomanip>
#include <chrono>
#define COUNT 200000
using FloatingPointMicroSeconds = std::chrono::duration<double, std::micro>;
struct Timer
{
    std::chrono::steady_clock::time_point start;
    Timer()
    {
        start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << std::setprecision(4) << std::fixed << "cost: " << (FloatingPointMicroSeconds(end.time_since_epoch()) - 
		FloatingPointMicroSeconds(start.time_since_epoch())).count() * 0.001 << "ms\n";
    }
};

int main(int argc, char const *argv[])
{
    {
        Timer t;
        std::stringstream ss;
        for (size_t i = 0; i < COUNT; i++)
        {
            ss << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        }
    }
    
    {
        Timer t;
        std::string ss;
        for (size_t i = 0; i < COUNT; i++)
        {
            ss += "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
        }
    }
    
    return 0;
}
