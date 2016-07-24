#pragma once
/******************************************************************************
The MIT License(MIT)

Copyright(c) 2016 Scott Slack-Smith

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/
#include <chrono>
#include <ostream>

class Stopwatch
{
public:

    struct Duration
    {
        Duration(Duration const&) = default;
        Duration(Duration&&) = default;
        Duration& operator=(Duration const&) = default;

        Duration(
            std::chrono::high_resolution_clock::time_point start,
            std::chrono::high_resolution_clock::time_point end
        )
        : myDuration(end-start)
        {
        }

        void print(std::ostream& os) const
        {
            long long count = myDuration.count();
            if (count < 1'000)
            {
                os << count << " nanosecs" << std::endl;
            }
            else if (count < 1'000'000)
            {
                using FractionalDuration = std::chrono::duration<double, std::micro>;
                os << FractionalDuration(myDuration).count() << " microsecs" << std::endl;
            }
            else if (count < 1'000'000'000)
            {
                using FractionalDuration = std::chrono::duration<double, std::milli>;
                os << FractionalDuration(myDuration).count() << " millisecs" << std::endl;
            }
            else if (count < 1'000'000'000'000)
            {
                using FractionalDuration = std::chrono::duration<double>;
                os << FractionalDuration(myDuration).count() << " secs" << std::endl;
            }
        }

        friend std::ostream& operator<<(std::ostream& os, const Duration& duration);

    private:

        std::chrono::nanoseconds myDuration;
    };

    Stopwatch()
        : m_start(std::chrono::high_resolution_clock::now())
    {
    }

    void reset()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    Duration elapsedTime() const
    {
        auto end = std::chrono::high_resolution_clock::now();
        return Duration(m_start,end);
    }

private:

    std::chrono::high_resolution_clock::time_point m_start;

};


std::ostream& operator<<(std::ostream& os, const Stopwatch::Duration& duration)
{
    duration.print(os);
    return os;
}
