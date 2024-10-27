#include <iostream>
#include "core/FIXSession.h"
#include "core/FIXParser.h"
#include "core/Logger.h"
#include "core/ConfigurationLoader.h"

int main() {
    // Load configuration settings
    ConfigurationLoader configLoader;
    if (!configLoader.loadConfig()) {
        std::cerr << "Failed to load configuration file." << std::endl;
        return 1;
    }

    // Initialize FIX session
    asio::io_context ioContext;
    FIXSession session(ioContext, configLoader.getServerHost(), configLoader.getServerPort());
    session.start();

    // Parse a sample FIX message
    FIXParser parser;
    std::string message = "8=FIX.4.2|35=D|55=AAPL|54=1|38=100|";
    if (parser.parseMessage(message)) {
        // Extract some fields from the parsed message
        std::string symbol = parser.getField("55").data();
        int side = std::stoi(parser.getField("54").data());
        int quantity = std::stoi(parser.getField("38").data());

        Logger::log(LogLevel::INFO, "Parsed Symbol: " + symbol);
        Logger::log(LogLevel::INFO, "Parsed Side: " + std::to_string(side));
        Logger::log(LogLevel::INFO, "Parsed Quantity: " + std::to_string(quantity));
    } else {
        Logger::log(LogLevel::ERROR, "Failed to parse FIX message.");
    }

    // Run the io_context to maintain the session
    ioContext.run();

    return 0;
}

