#pragma once

#include "Timer.hpp"

class ThreadTimer : public Timer {
public:
    void sleep_for(minutes duration) override {}
};