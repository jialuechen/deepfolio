#include "ErrorHandler.h"

ErrorHandler::ErrorHandler(int maxErrorCount)
    : errorCount_(0), maxErrorCount_(maxErrorCount) {}

// Handles an error: logs the error and increments the error count
void ErrorHandler::handleError(const std::string& errorMsg) {
    Logger::log(LogLevel::ERROR, errorMsg);
    ++errorCount_;
    if (hasReachedErrorThreshold()) {
        Logger::log(LogLevel::WARNING, "Error threshold reached. Consider restarting or resetting components.");
        // Additional recovery logic can be placed here, such as restarting sessions or alerting the system
    }
}

// Resets the error count, typically called after a successful recovery
void ErrorHandler::resetErrorCount() {
    errorCount_ = 0;
    Logger::log(LogLevel::INFO, "Error count reset.");
}

// Checks if the error threshold has been reached
bool ErrorHandler::hasReachedErrorThreshold() const {
    return errorCount_ >= maxErrorCount_;
}
