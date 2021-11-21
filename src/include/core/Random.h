#ifndef __RANDOM_H__
#define __RANDOM_H__
#include <random>
class Random
{
    public:
    static void init()
    {
        s_RandomSeed.seed(std::random_device()());
    }
    static float Float() 
    {
        return static_cast<float>(s_Distr(s_RandomSeed))/ static_cast<float>(std::numeric_limits<uint32_t>::max());
    }

    private:
    static std::mt19937 s_RandomSeed;
    static std::uniform_int_distribution<std::mt19937::result_type> s_Distr;

    
};
#endif // __RANDOM_H__