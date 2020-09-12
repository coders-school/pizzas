#pragma once
#include <thread>

#include "Timer.hpp"

class DummyTimer : public Timer {
public:
    void sleep_for(minutes duration) override {}
};
