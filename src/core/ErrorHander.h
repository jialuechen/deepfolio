#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <string>
#include "Logger.h"

class ErrorHandler {
public:
    // Constructor to initialize error handler with a max error count threshold
    ErrorHandler(int maxErrorCount = 5);

    // Logs an error message and increments the error count
    void handleError(const std::string& errorMsg);

    // Resets the error count, typically called after a successful recovery
    void resetErrorCount();

    // Checks if the maximum error threshold has been reached
    bool hasReachedErrorThreshold() const;

private:
    int errorCount_;         // Current error count
    int maxErrorCount_;      // Maximum allowable errors before triggering a recovery or restart
};

#endif // ERRORHANDLER_H
