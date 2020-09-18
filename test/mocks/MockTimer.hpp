#pragma once

#include <gmock/gmock.h>
#include "../../src/Timer.hpp"

class MockTimer : public Timer {
public:
    MockTimer() : Timer() {}
    MOCK_METHOD(void, sleepFor, (minutes duration), (override));
};
