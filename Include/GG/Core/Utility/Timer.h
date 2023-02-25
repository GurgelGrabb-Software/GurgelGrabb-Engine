#pragma once

namespace gg
{
    class CTimer
    {
    public:
        CTimer();

        float Reset();

        float GetTotalTime() const;

    private:

        unsigned long _previous;
        unsigned long _start;
    };
}