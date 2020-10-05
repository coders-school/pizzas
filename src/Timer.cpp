#include "Timer.hpp"

Timer::Timer(){};

void Timer::sleep_for(minutes time_) const { std::this_thread::sleep_for(time_); }
