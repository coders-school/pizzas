#pragma once
#include <thread>

#include "Timer.hpp"

using minutes = std::chrono::seconds;   // To simulate time flow ;)

class ThreadTimer : public Timer {
public:
    void sleep_for(minutes duration) override {
        std::this_thread::sleep_for(duration);
    }
};