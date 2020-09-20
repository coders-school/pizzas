#pragma once

#include "Timer.hpp"
#include "gmock/gmock.h"

struct TimerMock : public Timer {
    MOCK_METHOD(void, sleep_for, (minutes), (override));
};