#include "Authenticator.h"

Authenticator::Authenticator(asio::io_context& io_context, asio::ssl::context& ssl_context)
    : ssl_socket_(io_context, ssl_context) {}

// Connects to the server with SSL/TLS support
void Authenticator::connect(const std::string& host, const std::string& port) {
    try {
        asio::ip::tcp::resolver resolver(ssl_socket_.get_io_context());
        auto endpoints = resolver.resolve(host, port);

        // Initiates a connection to the server
        asio::connect(ssl_socket_.lowest_layer(), endpoints);

        Logger::log(LogLevel::INFO, "Connected to server " + host + ":" + port);
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "Failed to connect: " + std::string(e.what()));
    }
}

// Sets the API key if using API-based authentication
void Authenticator::setApiKey(const std::string& apiKey) {
    api_key_ = apiKey;
}

// Performs SSL handshake and optional API key-based authentication
bool Authenticator::authenticate() {
    try {
        ssl_socket_.handshake(asio::ssl::stream_base::client);
        Logger::log(LogLevel::INFO, "SSL/TLS handshake successful.");

        // If an API key is provided, send it as part of the authentication (optional)
        if (!api_key_.empty()) {
            asio::write(ssl_socket_, asio::buffer(api_key_));
            Logger::log(LogLevel::INFO, "API key sent for authentication.");
        }

        return true;
    } catch (const std::exception& e) {
        Logger::log(LogLevel::ERROR, "Authentication failed: " + std::string(e.what()));
        return false;
    }
}

// Returns the SSL socket for further communication
asio::ssl::stream<asio::ip::tcp::socket>& Authenticator::getSocket() {
    return ssl_socket_;
}
