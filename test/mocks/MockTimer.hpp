#pragma once
#include "ThreadTimer.hpp"
#include "gmock/gmock.h"

class MockTimer : public ThreadTimer {
public:
    MOCK_METHOD(void, sleep_for, (minutes duration), (override));
};
