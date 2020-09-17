#pragma once

#include <gmock/gmock.h>

#include "Timer.hpp"

class TimeMock : public Timer {
public:
    MOCK_METHOD(void, sleep_for, (minutes duration), (override));
};