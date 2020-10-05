#pragma once

#include <chrono>
#include <thread>

using minutes = std::chrono::seconds; 

class ITimer {
    public:
        virtual ~ITimer() = default;
        virtual void sleep_for(minutes) const = 0;
};
