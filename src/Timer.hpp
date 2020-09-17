#pragma once
#include <chrono>
using minutes = std::chrono::seconds;  // To simulate time flow ;)

class Timer {
public:
    virtual ~Timer() = default;
    virtual void sleepFor(minutes) = 0;
};