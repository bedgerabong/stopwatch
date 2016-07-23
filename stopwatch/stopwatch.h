#pragma once
#include <chrono>
#include <ostream>

class Stopwatch
{
public:

    struct Duration
    {

    };

    Stopwatch()
        : m_start(std::chrono::high_resolution_clock::now())
    {
    }

    void reset()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    template<typename TimeUnits>
    TimeUnits elapsedTime() const
    {
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<TimeUnits>(end - m_start);
        return elapsedTime;
    }

private:

    std::chrono::high_resolution_clock::time_point m_start;

};


std::ostream& operator<<(std::ostream& os, const std::chrono::seconds& duration)
{
    os << duration.count() << " seconds" << std::endl;
    return os;
}


std::ostream& operator<<(std::ostream& os, const std::chrono::milliseconds& duration)
{
    os << duration.count() << " milliseconds" << std::endl;
    return os;
}


std::ostream& operator<<(std::ostream& os, const std::chrono::microseconds& duration)
{
    os << duration.count() << " microseconds" << std::endl;
    return os;
}

std::ostream& operator<<(std::ostream& os, const std::chrono::nanoseconds& duration)
{
    os << duration.count() << " nanoseconds" << std::endl;
    return os;
}