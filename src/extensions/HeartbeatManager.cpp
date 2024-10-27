#include "HeartbeatManager.h"

HeartbeatManager::HeartbeatManager(asio::io_context& io_context, int intervalSeconds, TimeoutHandler timeoutHandler)
    : timer_(io_context), intervalSeconds_(intervalSeconds), timeoutHandler_(timeoutHandler) {}

// Starts the heartbeat timer
void HeartbeatManager::start() {
    reset();
}

// Resets the heartbeat timer (e.g., when a response is received from the server)
void HeartbeatManager::reset() {
    timer_.expires_after(std::chrono::seconds(intervalSeconds_));
    timer_.async_wait([this](const asio::error_code& error) {
        onTimeout(error);
    });
}

// Sends a heartbeat message and resets the timer
void HeartbeatManager::sendHeartbeat() {
    Logger::log(LogLevel::DEBUG, "Sending heartbeat message.");
    // Reset timer after sending the heartbeat
    reset();
}

// Handles a timeout event if the server did not respond in time
void HeartbeatManager::onTimeout(const asio::error_code& error) {
    if (!error) {
        Logger::log(LogLevel::WARNING, "Heartbeat timeout detected.");
        if (timeoutHandler_) {
            timeoutHandler_();
        }
    } else if (error != asio::error::operation_aborted) {
        Logger::log(LogLevel::ERROR, "Heartbeat error: " + error.message());
    }
}