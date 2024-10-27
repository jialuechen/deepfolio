#include <iostream>
#include "core/FIXSession.h"
#include "core/ConfigurationLoader.h"
#include "extensions/RiskControl.h"
#include "extensions/OrderRateLimiter.h"
#include "extensions/MessageReplay.h"
#include "extensions/LatencyOptimizer.h"
#include "extensions/LoadBalancer.h"
#include "extensions/AuditLog.h"
#include "core/Logger.h"

int main() {
    // Load configuration settings
    ConfigurationLoader configLoader;
    if (!configLoader.loadConfig()) {
        std::cerr << "Failed to load configuration file." << std::endl;
        return 1;
    }

    // Initialize asio context and FIX session
    asio::io_context ioContext;
    FIXSession session(ioContext, configLoader.getServerHost(), configLoader.getServerPort());
    session.start();

    // Initialize Risk Control
    RiskControl riskControl;
    if (!riskControl.checkOrderLimits(150000)) {
        Logger::log(LogLevel::WARNING, "Order amount exceeds limit.");
    }

    // Initialize Rate Limiter
    OrderRateLimiter rateLimiter(configLoader.getMaxOrdersPerMinute());
    if (!rateLimiter.canSendOrder()) {
        Logger::log(LogLevel::WARNING, "Order rate limit exceeded.");
    }

    // Initialize Message Replay
    MessageReplay messageReplay(1000);
    std::string sampleMessage = "8=FIX.4.2|35=D|55=AAPL|54=1|38=100|";
    messageReplay.recordMessage("session1", sampleMessage);

    // Retrieve messages since a given sequence number
    auto replayMessages = messageReplay.getMessagesSince("session1", 1);
    for (const auto& msg : replayMessages) {
        Logger::log(LogLevel::INFO, "Replayed Message: " + msg);
    }

    // Initialize Latency Optimizer and Load Balancer
    LatencyOptimizer latencyOptimizer;
    LoadBalancer loadBalancer(&latencyOptimizer);

    // Register sessions and update latencies for demonstration
    loadBalancer.registerSession("session1");
    latencyOptimizer.updateLatency("session1", std::chrono::microseconds(100));

    loadBalancer.registerSession("session2");
    latencyOptimizer.updateLatency("session2", std::chrono::microseconds(50));

    std::string optimalSession = loadBalancer.selectSession();
    Logger::log(LogLevel::INFO, "Selected optimal session: " + optimalSession);

    // Initialize Audit Log
    AuditLog auditLog("audit_log.txt");
    auditLog.logEvent("Session started for advanced usage example.");

    // Run the io_context to maintain the session
    ioContext.run();

    return 0;
}
