#pragma once

#include "../../src/Timer.hpp"

class DummyTimer : public Timer {
    void sleepFor(minutes duration) override { (void)duration; }
};
