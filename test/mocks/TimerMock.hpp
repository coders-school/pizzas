#include "Timer.hpp"
#include "gmock/gmock.h"

struct TimerMock : public Timer {
    TimerMock(){}
    MOCK_METHOD(void, sleep_for, (minutes duration), (override));

};
