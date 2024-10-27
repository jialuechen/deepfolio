#include "Logger.h"

LogLevel Logger::logLevel_ = LogLevel::INFO;
std::mutex Logger::logMutex_;

void Logger::setLogLevel(LogLevel level) {
    logLevel_ = level;
}

void Logger::log(LogLevel level, const std::string& message) {
    if (level >= logLevel_) {
        std::lock_guard<std::mutex> lock(logMutex_);
        std::cout << "[LOG - " << toString(level) << "]: " << message << std::endl;
    }
}

std::string Logger::toString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::DEBUG: return "DEBUG";
    }
    return "UNKNOWN";
}
