#pragma once
#include <thread>
#include "Timer.hpp"

class ThreadTimer : public Timer {
public:
    virtual void sleep_for(minutes duration) override{
        std::this_thread::sleep_for(duration);
    }
};
