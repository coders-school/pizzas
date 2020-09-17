#pragma once
#include "Timer.hpp"

class DummyTimer : public Timer {
public:
    void sleepFor(minutes duration) override {}
};
