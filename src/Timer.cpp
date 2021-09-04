#include "Timer.h"
#include <iostream>

Timer::Timer(const char* nfo) : info(nfo)
{
   start = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    std::cout << info << " --> Timer: " << duration.count() * 1000  << "ms "<<std::endl;
}
