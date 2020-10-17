#pragma once
#include "Timer.hpp"

class MockTimer : public Timer {
public:
    void sleep_for(minutes duration) override
    {
    }
};