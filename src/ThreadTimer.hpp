#pragma once
#include "Timer.hpp"

#include <thread>

class ThreadTimer : Timer {
public:
    void sleep_for(minutes duration)
    {
        std::this_thread::sleep_for(duration);
    }
};