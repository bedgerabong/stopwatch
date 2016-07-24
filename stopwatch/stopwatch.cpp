// stopwatch.cpp : Defines the entry point for the console application.
//

#include "stopwatch.h"
#include <iostream>


int main()
{
    {
        Stopwatch spotwatch;
        size_t sum{};
        for (size_t i=0; i< 1'000; ++i)
        {
            sum += i;
        }
        std::cout << spotwatch.elapsedTime() << std::endl;
        std::cout << sum << std::endl;
    }
    return 0;
}

