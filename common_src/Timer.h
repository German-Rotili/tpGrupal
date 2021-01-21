#ifndef __TIMER_H__
#define __TIMER_H__

#include <chrono>



class Timer
{
private:
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end;
    bool running = false;
public:
    Timer();
    ~Timer();
    void start();
    int elapsed_time();
    bool is_running();
};



#endif // __TIMER_H__