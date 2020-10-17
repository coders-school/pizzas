#pragma once
#include "gmock/gmock.h"
#include "ThreadTimer.hpp"


class MockTimer : public ThreadTimer {
public:
    MOCK_METHOD(void, sleep_for,(minutes duration), (override));
};