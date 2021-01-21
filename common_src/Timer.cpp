#include <chrono>
#include "Timer.h"







void Timer::start(){
    this->running = true;
    this->begin = std::chrono::steady_clock::now();

}


int Timer::elapsed_time() {
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    return   std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    
}

bool Timer::is_running(){
    return this->running;
}



