#ifndef FIXCONNECTION_H
#define FIXCONNECTION_H

#include <asio.hpp>
#include <string>
#include <functional>
#include <iostream>
#include "Logger.h"

class FIXConnection {
public:
    using MessageHandler = std::function<void(const std::string&)>;

    // Constructor: initializes socket and sets up server details
    FIXConnection(asio::io_context& io_context, const std::string& host, const std::string& port);

    // Establishes a connection to the server
    void connect();

    // Sends a FIX message to the server
    void send(const std::string& message);

    // Sets a callback handler for incoming messages
    void setMessageHandler(MessageHandler handler);

    // Starts asynchronous receiving of messages
    void startReceive();

private:
    // Internal function to handle received messages
    void handleReceive(const asio::error_code& error, std::size_t bytes_transferred);

    // Internal function to handle sending messages
    void handleSend(const asio::error_code& error, std::size_t bytes_transferred);

    asio::ip::tcp::socket socket_;
    asio::ip::tcp::resolver resolver_;
    std::string host_;
    std::string port_;
    std::string readBuffer_;
    MessageHandler messageHandler_;
};

#endif // FIXCONNECTION_H
