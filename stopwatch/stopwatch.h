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

/** A basic stopwatch that uses a high resolution clock.

Usage example:
    {
        Stopwatch stopwatch;
        ...
        std::cout << stopwatch.elapsedTime() << std::endl;
    }

Notes:

*   For Visual Studio 2015 & greater the implementation of high_resolution_clock 
    was changed to meet the C++ Standard requirements for steadiness and monotonicity 
    and is implemeneted by using the OS function QueryPerformanceCounter which 
    is the highest resolution and most accurate timer available on Windows. 



*/
class Stopwatch
{
public:

    // Delete any copy operations as it doesn't make sense to make a copy.
    Stopwatch(Stopwatch const&) = delete;
    Stopwatch& operator=(Stopwatch const&) = delete;

    /// Default ctor that sets the stopwatch's start time
    Stopwatch()
    :   myStartTime(std::chrono::high_resolution_clock::now())
    {
    }

    // Reset the stopwatch's start time
    void reset()
    {
        myStartTime = std::chrono::high_resolution_clock::now();
    }

    // Add forward declaration so we can add Duration's defintion
    // after the declaration of elapsedTime()
    struct Duration;

    // Get the elapsed time since the stopwatch's start time
    Duration elapsedTime() const
    {
        auto endTime = std::chrono::high_resolution_clock::now();
        return Duration(myStartTime, endTime);
    }

    // Helper class that allows us to provide a convenient std::ostream override.
    // Usage example:
    //     Stopwatch stopwatch;
    //         ...
    //     std::cout << stopwatch.elapsedTime() << std::endl;
    struct Duration
    {
        Duration(
            std::chrono::high_resolution_clock::time_point startTime,
            std::chrono::high_resolution_clock::time_point endTime
        )
        :   myDuration(endTime - startTime)
        {
        }

        // Rescale to most convenient time units (secs, millisecs etc..) and print the elapsed time 
        void print(std::ostream& os) const
        {
            auto const count = std::chrono::nanoseconds(myDuration).count();
            if (count < 1'000) // print as nanoseconds
            {
                using FractionalDuration = std::chrono::duration<double, std::nano>;
                os << FractionalDuration(myDuration).count() << " nanosecs";
            }
            else if (count < 1'000'000) // rescale and print as microoseconds
            {
                using FractionalDuration = std::chrono::duration<double, std::micro>;
                os << FractionalDuration(myDuration).count() << " microsecs";
            }
            else if (count < 1'000'000'000)
            {
                using FractionalDuration = std::chrono::duration<double, std::milli>;
                os << FractionalDuration(myDuration).count() << " millisecs";
            }
            else
            {
                using FractionalDuration = std::chrono::duration<double>;
                os << FractionalDuration(myDuration).count() << " secs";
            }
        }

        // Add a convenient std::ostream override which allows us to:
        //     std::cout << stopwatch.elapsedTime() << std::endl;
        friend std::ostream& operator<<(std::ostream& os, const Duration& duration)
        {
            duration.print(os);
            return os;
        }

    private:
        // The elapsed time 
        std::chrono::high_resolution_clock::duration myDuration;
    };

private:
    // The stopwatch's start time 
    std::chrono::high_resolution_clock::time_point myStartTime;
};
