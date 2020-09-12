#pragma once
#include <gmock/gmock.h>
#include "Timer.hpp"

class MockTimer : public Timer {
public:
    MOCK_METHOD(void, sleep_for, (minutes), (override));
};