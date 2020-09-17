#include "Pizza.hpp"
#include "gmock/gmock.h"

class TimerMock : public Timer {
    public:
    TimerMock() : Timer() {}
    MOCK_METHOD(void, sleepFor, (minutes duration), (override));
};
