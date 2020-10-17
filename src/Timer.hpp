#pragma once

#include <chrono>

using minutes = std::chrono::seconds;

class Timer {
public:
    virtual ~Timer();
    virtual void sleep_for(minutes) = 0;

};