#include "core/profiling/Timer.h"
#include <iostream>
#include <core/Log.h>


Timer::Timer(const char* nfo) : info(nfo)
{
   start = std::chrono::high_resolution_clock::now();
}


Timer::~Timer()
{
    end = std::chrono::high_resolution_clock::now();
    duration = end - start;
    DE_CORE_INFO("{0} ---> Timer: {1}ms", info, duration.count() * 1000);
}
