#include <thread>

#include "ThreadTimer.hpp"

void ThreadTimer::sleepFor(minutes duration) {
    std::this_thread::sleep_for(duration);
}
