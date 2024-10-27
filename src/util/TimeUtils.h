#ifndef TIMEUTILS_H
#define TIMEUTILS_H

#include <chrono>
#include <string>
#include <iomanip>
#include <sstream>

class TimeUtils {
public:
    // Returns the current time as a formatted string
    static std::string getCurrentTimestamp() {
        auto now = std::chrono::system_clock::now();
        auto time = std::chrono::system_clock::to_time_t(now);
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&time), "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    // Returns the current time as a high-precision timestamp in microseconds
    static long long getCurrentTimeMicroseconds() {
        auto now = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
    }

    // Measures and returns the elapsed time in microseconds between two time points
    template <typename TimePoint>
    static long long calculateElapsedMicroseconds(const TimePoint& start, const TimePoint& end) {
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
};

#endif // TIMEUTILS_H
