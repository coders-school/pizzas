#pragma once

#include "Timer.hpp"

using minutes = std::chrono::seconds;   // To simulate time flow ;)

class DummyTimer : public Timer {
public:
    void sleep_for(minutes duration) override {}
};