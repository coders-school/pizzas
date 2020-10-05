#pragma once

#include "ITimer.hpp"
#include "gmock/gmock.h"


struct TimerMock : public ITimer
{
    MOCK_METHOD(void, sleep_for, (minutes), (const, override));
    MOCK_METHOD(std::chrono::system_clock::time_point, now,  (), (const, override));
};


