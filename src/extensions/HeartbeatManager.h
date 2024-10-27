#ifndef HEARTBEATMANAGER_H
#define HEARTBEATMANAGER_H

#include <asio.hpp>
#include <functional>
#include <chrono>
#include "Logger.h"

class HeartbeatManager {
public:
    using TimeoutHandler = std::function<void()>;

    // Constructor that initializes the manager with a heartbeat interval and an optional timeout handler
    HeartbeatManager(asio::io_context& io_context, int intervalSeconds, TimeoutHandler timeoutHandler = nullptr);

    // Starts the heartbeat timer
    void start();

    // Resets the timer (called upon receiving a heartbeat or any other response from the server)
    void reset();

    // Sends a heartbeat message and re-arms the timer
    void sendHeartbeat();

private:
    void onTimeout(const asio::error_code& error);

    asio::steady_timer timer_;
    int intervalSeconds_;
    TimeoutHandler timeoutHandler_;
};

#endif // HEARTBEATMANAGER_H
