#ifndef TIMER_H_
#define TIMER_H_

#include<chrono>


class Timer{
    public:
            Timer(const char* nfo);
            ~Timer();


    private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> duration;
            const char* info;




};


#endif // TIMER_H_
