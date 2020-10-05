#pragma once

#include "ITimer.hpp"
#include <chrono>

class Timer : public ITimer {
    public:
         ~Timer(){};
         Timer();
        void sleep_for(minutes) const override;
};
