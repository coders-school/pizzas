#pragma once
#include <thread>
#include "Timer.hpp"
class ThreadTimer : public Timer {
public:
    void sleepFor(minutes duration) override {
        std::this_thread::sleep_for(duration);
    }
};