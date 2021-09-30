#pragma once

#include <chrono>
#include <gmock/gmock.h>

class Timer {
   public:
    virtual ~Timer() = default;
    virtual void sleep_for(std::chrono::seconds) = 0;
};

struct TimerMock : public Timer {
    MOCK_METHOD(void, sleep_for, (std::chrono::seconds), (override));  
};
