#pragma once
#include "Timer.hpp"

class DummyTimer : Timer {
public:
    void sleep_for(minutes duration)
    {
    }
};