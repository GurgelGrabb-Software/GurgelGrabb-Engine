#include "GG/Core/Utility/Timer.h"

#include <chrono>

using namespace gg;
using namespace std::chrono;

CTimer::CTimer()
{
    _previous = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    _start = _previous;
}

float CTimer::Reset()
{
    size_t now = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    float seconds = (now - _previous) / 1000000.f;
    _previous = now;
    return seconds;
}

float CTimer::GetTotalTime() const
{
    size_t now = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count();
    float seconds = (now - _start) / 1000000.f;
    return seconds;
}