#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <string>
#include <memory>
#include "Logger.h"

class Authenticator {
public:
    // Constructor that sets up the SSL context and socket
    Authenticator(asio::io_context& io_context, asio::ssl::context& ssl_context);

    // Initiates a connection to the given host and port with SSL/TLS support
    void connect(const std::string& host, const std::string& port);

    // Sets an API key for authentication (optional for cases where both API key and SSL are used)
    void setApiKey(const std::string& apiKey);

    // Authenticates the connection using SSL handshake and optional API key
    bool authenticate();

    // Retrieves the underlying SSL socket for further use
    asio::ssl::stream<asio::ip::tcp::socket>& getSocket();

private:
    asio::ssl::stream<asio::ip::tcp::socket> ssl_socket_;
    std::string api_key_;
};

#endif // AUTHENTICATOR_H
