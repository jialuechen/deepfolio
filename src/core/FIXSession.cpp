#include "FIXSession.h"
#include <asio/write.hpp>

FIXSession::FIXSession(asio::io_context& io_context)
    : socket_(io_context), timer_(io_context) {}

void FIXSession::start() {
    startHeartbeat();
}

void FIXSession::onMessageReceived(const std::string& message) {
    if (parser_.parseMessage(message)) {
        processMessage();
    }
}

void FIXSession::startHeartbeat() {
    timer_.expires_after(std::chrono::seconds(30));
    timer_.async_wait([this](std::error_code ec) {
        if (!ec) {
            sendHeartbeat();
            startHeartbeat();
        }
    });
}

void FIXSession::sendHeartbeat() {
    std::string heartbeat_msg = parser_.buildMessage({{"35", "0"}, {"34", std::to_string(sequence_number_++)}});
    asio::async_write(socket_, asio::buffer(heartbeat_msg), [](std::error_code, std::size_t) {});
}

void FIXSession::processMessage() {
    // Handle different message types
}
