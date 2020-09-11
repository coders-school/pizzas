#pragma once

#include <thread>

#include "Timer.hpp"

class DummyTimer : public Timer {
public:
    void sleepFor(minutes duration) override{};
};
