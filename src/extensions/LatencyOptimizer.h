#ifndef LATENCYOPTIMIZER_H
#define LATENCYOPTIMIZER_H

#include <unordered_map>
#include <string>
#include <chrono>
#include <limits>

class LatencyOptimizer {
public:
    // Updates the latency measurement for a specific session
    void updateLatency(const std::string& sessionId, std::chrono::microseconds latency);

    // Retrieves the session ID with the lowest recorded latency
    std::string getLowestLatencySession() const;

    // Retrieves the current latency for a specific session
    std::chrono::microseconds getLatency(const std::string& sessionId) const;

private:
    std::unordered_map<std::string, std::chrono::microseconds> latencyMap_;
};

#endif // LATENCYOPTIMIZER_H
