#pragma once
#include "Timer.hpp"

class DummyTimer : Timer {
public:
    void sleep(minutes duration)
    {
    }
};