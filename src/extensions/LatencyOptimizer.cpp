#include "LatencyOptimizer.h"
#include <stdexcept>

// Updates the latency measurement for a specific session
void LatencyOptimizer::updateLatency(const std::string& sessionId, std::chrono::microseconds latency) {
    latencyMap_[sessionId] = latency;
}

// Retrieves the session ID with the lowest recorded latency
std::string LatencyOptimizer::getLowestLatencySession() const {
    if (latencyMap_.empty()) {
        throw std::runtime_error("No sessions available to determine lowest latency.");
    }

    std::string lowestLatencySession;
    auto lowestLatency = std::chrono::microseconds::max();

    for (const auto& [sessionId, latency] : latencyMap_) {
        if (latency < lowestLatency) {
            lowestLatency = latency;
            lowestLatencySession = sessionId;
        }
    }

    return lowestLatencySession;
}

// Retrieves the current latency for a specific session
std::chrono::microseconds LatencyOptimizer::getLatency(const std::string& sessionId) const {
    auto it = latencyMap_.find(sessionId);
    if (it != latencyMap_.end()) {
        return it->second;
    } else {
        throw std::runtime_error("Session ID not found: " + sessionId);
    }
}
