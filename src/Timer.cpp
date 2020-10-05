#include "Timer.hpp"

Timer::Timer(){};

void Timer::sleep_for(minutes time_) const { std::this_thread::sleep_for(time_); }
std::chrono::system_clock::time_point  Timer::now() const  { return std::chrono::system_clock::now(); } 
