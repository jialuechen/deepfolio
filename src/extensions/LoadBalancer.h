#ifndef LOADBALANCER_H
#define LOADBALANCER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include "LatencyOptimizer.h"

class LoadBalancer {
public:
    // Constructor: Initializes with an optional LatencyOptimizer for latency-based balancing
    explicit LoadBalancer(LatencyOptimizer* latencyOptimizer = nullptr);

    // Registers a session with an initial load count
    void registerSession(const std::string& sessionId);

    // Removes a session from the load balancer
    void removeSession(const std::string& sessionId);

    // Updates the load count for a specific session
    void updateLoad(const std::string& sessionId, int load);

    // Selects the optimal session based on load or latency
    std::string selectSession() const;

private:
    std::unordered_map<std::string, int> sessionLoadMap_; // Maps session IDs to load counts
    LatencyOptimizer* latencyOptimizer_;                  // Optional latency optimizer for latency-based selection
    mutable std::mt19937 randomEngine_;                   // Random number generator for load balancing

    // Selects a session based on the lowest load count
    std::string selectLowestLoadSession() const;

    // Selects a session with the lowest latency if a LatencyOptimizer is available
    std::string selectLowestLatencySession() const;
};

#endif // LOADBALANCER_H
