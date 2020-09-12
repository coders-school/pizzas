#pragma once
#include "Timer.hpp"

class DummyTimer : public Timer {
public:
    virtual void sleep_for(minutes duration) override {}
};
