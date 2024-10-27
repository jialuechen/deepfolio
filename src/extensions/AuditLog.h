#ifndef AUDITLOG_H
#define AUDITLOG_H

#include <fstream>
#include <string>
#include <mutex>
#include "TimeUtils.h"

class AuditLog {
public:
    // Constructor to initialize the log file with the specified filename
    explicit AuditLog(const std::string& filename);

    // Destructor to close the log file if it's open
    ~AuditLog();

    // Logs an event with a timestamp in the audit log file
    void logEvent(const std::string& event);

private:
    std::ofstream logFile_;     // Output file stream for the log file
    std::mutex logMutex_;       // Mutex for thread-safe logging
};

#endif // AUDITLOG_H
