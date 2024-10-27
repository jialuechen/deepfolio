#include "AuditLog.h"
#include "Logger.h"

AuditLog::AuditLog(const std::string& filename) {
    logFile_.open(filename, std::ios::app);
    if (!logFile_.is_open()) {
        Logger::log(LogLevel::ERROR, "Failed to open audit log file: " + filename);
    } else {
        Logger::log(LogLevel::INFO, "Audit log file opened: " + filename);
    }
}

AuditLog::~AuditLog() {
    if (logFile_.is_open()) {
        logFile_.close();
        Logger::log(LogLevel::INFO, "Audit log file closed.");
    }
}

// Logs an event with a timestamp, ensuring thread safety
void AuditLog::logEvent(const std::string& event) {
    std::lock_guard<std::mutex> lock(logMutex_);
    if (logFile_.is_open()) {
        logFile_ << "[" << TimeUtils::getCurrentTimestamp() << "] " << event << std::endl;
    } else {
        Logger::log(LogLevel::ERROR, "Attempted to log event, but audit log file is not open.");
    }
}
