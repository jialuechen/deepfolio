#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <mutex>

enum class LogLevel { INFO, WARNING, ERROR, DEBUG };

class Logger {
public:
    static void setLogLevel(LogLevel level);
    static void log(LogLevel level, const std::string& message);

private:
    static LogLevel logLevel_;
    static std::mutex logMutex_;
    static std::string toString(LogLevel level);
};

#endif // LOGGER_H
