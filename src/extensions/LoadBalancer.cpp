#include "LoadBalancer.h"
#include <stdexcept>
#include <algorithm>

LoadBalancer::LoadBalancer(LatencyOptimizer* latencyOptimizer)
    : latencyOptimizer_(latencyOptimizer), randomEngine_(std::random_device{}()) {}

// Registers a session with an initial load count of zero
void LoadBalancer::registerSession(const std::string& sessionId) {
    sessionLoadMap_[sessionId] = 0;
}

// Removes a session from the load balancer
void LoadBalancer::removeSession(const std::string& sessionId) {
    sessionLoadMap_.erase(sessionId);
}

// Updates the load count for a specific session
void LoadBalancer::updateLoad(const std::string& sessionId, int load) {
    if (sessionLoadMap_.find(sessionId) != sessionLoadMap_.end()) {
        sessionLoadMap_[sessionId] = load;
    } else {
        throw std::runtime_error("Session ID not found: " + sessionId);
    }
}

// Selects the optimal session based on either lowest load or lowest latency
std::string LoadBalancer::selectSession() const {
    if (latencyOptimizer_) {
        return selectLowestLatencySession();
    }
    return selectLowestLoadSession();
}

// Selects a session with the lowest load count
std::string LoadBalancer::selectLowestLoadSession() const {
    if (sessionLoadMap_.empty()) {
        throw std::runtime_error("No sessions registered for load balancing.");
    }

    auto lowestLoadSession = std::min_element(
        sessionLoadMap_.begin(),
        sessionLoadMap_.end(),
        [](const auto& lhs, const auto& rhs) {
            return lhs.second < rhs.second;
        });

    return lowestLoadSession->first;
}

// Selects a session with the lowest latency using LatencyOptimizer if available
std::string LoadBalancer::selectLowestLatencySession() const {
    try {
        return latencyOptimizer_->getLowestLatencySession();
    } catch (const std::runtime_error&) {
        // Fall back to load-based balancing if latency information is unavailable
        return selectLowestLoadSession();
    }
}
