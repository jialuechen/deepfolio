#ifndef FIXSESSION_H
#define FIXSESSION_H

#include <asio.hpp>
#include <chrono>
#include "FIXParser.h"

class FIXSession {
public:
    FIXSession(asio::io_context& io_context);

    void start();
    void onMessageReceived(const std::string& message);

private:
    void startHeartbeat();
    void sendHeartbeat();
    void processMessage();

    asio::ip::tcp::socket socket_;
    asio::steady_timer timer_;
    FIXParser parser_;
    int sequence_number_ = 1;
};

#endif // FIXSESSION_H
