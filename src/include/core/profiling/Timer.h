#ifndef TIMER_H_
#define TIMER_H_

#include<chrono>
#include <GLFW/glfw3.h>


class Timer{
    public:
            Timer(const char* nfo);
            ~Timer();
            static std::chrono::time_point<std::chrono::high_resolution_clock> GetTime()  
            { 
                return std::chrono::high_resolution_clock::now();
            }

            static float GetTimeFloat() {   return glfwGetTime();  }
        

            
           


    private:
            std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
            std::chrono::duration<float> duration;
            const char* info;




};


namespace Demon {

using time = std::chrono::time_point<std::chrono::high_resolution_clock>;
using duration = std::chrono::duration<float>;

}


#endif // TIMER_H_
