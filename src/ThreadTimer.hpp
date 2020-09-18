#pragma once

#include "Timer.hpp"

class ThreadTimer : public Timer {
public:
    void sleepFor(minutes duration) override;
};
