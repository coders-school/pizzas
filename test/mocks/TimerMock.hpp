#include "Timer.hpp"
#include "gmock/gmock.h"

class DummyTimer : public Timer {
public:
    void sleep_for(minutes duration) override {}
};

class TimerMock : public Timer {
public:
    MOCK_METHOD(void, sleep_for, (minutes duration), (override));
};
