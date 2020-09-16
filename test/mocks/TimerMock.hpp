#pragma once

#include "Timer.hpp"
#include "gmock/gmock.h"

class TimerMock : public Timer {
public:
    MOCK_METHOD(void, sleep_for, (minutes), (override));
};