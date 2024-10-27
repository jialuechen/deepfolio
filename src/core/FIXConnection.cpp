#include "FIXConnection.h"

FIXConnection::FIXConnection(asio::io_context& io_context, const std::string& host, const std::string& port)
    : socket_(io_context), resolver_(io_context), host_(host), port_(port) {}

// Establishes a connection to the FIX server
void FIXConnection::connect() {
    auto endpoints = resolver_.resolve(host_, port_);
    asio::async_connect(socket_, endpoints,
        [this](std::error_code ec, asio::ip::tcp::endpoint) {
            if (!ec) {
                Logger::log(LogLevel::INFO, "Connected to FIX server at " + host_ + ":" + port_);
                startReceive();  // Start receiving messages once connected
            } else {
                Logger::log(LogLevel::ERROR, "Failed to connect to FIX server: " + ec.message());
            }
        });
}

// Sends a FIX message to the server
void FIXConnection::send(const std::string& message) {
    asio::async_write(socket_, asio::buffer(message),
        [this](std::error_code ec, std::size_t bytes_transferred) {
            handleSend(ec, bytes_transferred);
        });
}

// Sets the callback handler for incoming messages
void FIXConnection::setMessageHandler(MessageHandler handler) {
    messageHandler_ = std::move(handler);
}

// Starts asynchronous message receiving
void FIXConnection::startReceive() {
    asio::async_read_until(socket_, asio::dynamic_buffer(readBuffer_), '|',
        [this](std::error_code ec, std::size_t bytes_transferred) {
            handleReceive(ec, bytes_transferred);
        });
}

// Handles message receipt and triggers the message handler callback
void FIXConnection::handleReceive(const asio::error_code& error, std::size_t bytes_transferred) {
    if (!error) {
        // Extract the message from the buffer
        std::string message(readBuffer_.substr(0, bytes_transferred));
        readBuffer_.erase(0, bytes_transferred);  // Remove processed message from buffer

        // Invoke the message handler callback if set
        if (messageHandler_) {
            messageHandler_(message);
        }

        // Continue receiving the next message
        startReceive();
    } else {
        Logger::log(LogLevel::ERROR, "Error receiving message: " + error.message());
    }
}

// Logs successful message send and handles any errors
void FIXConnection::handleSend(const asio::error_code& error, std::size_t bytes_transferred) {
    if (error) {
        Logger::log(LogLevel::ERROR, "Error sending message: " + error.message());
    } else {
        Logger::log(LogLevel::DEBUG, "Sent message of " + std::to_string(bytes_transferred) + " bytes.");
    }
}
