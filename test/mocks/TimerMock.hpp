#pragma once

#include <thread>
#include "gmock/gmock.h"

#include "Timer.hpp"

struct TimeMock : public Timer {
    MOCK_METHOD(void, sleep_for, (minutes), (override));
};
