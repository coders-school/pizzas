#pragma once
#include <chrono>

using minutes = std::chrono::seconds;

class Timer {
public:
    virtual ~Timer() = default;
    virtual void sleep_for(minutes) = 0;
};
