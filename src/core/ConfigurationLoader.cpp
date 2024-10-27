#include "ConfigurationLoader.h"

ConfigurationLoader::ConfigurationLoader(const std::string& configFile)
    : configFile_(configFile) {}

// Loads and parses the configuration JSON file
bool ConfigurationLoader::loadConfig() {
    if (!JSONParser::loadJSON(configFile_, configRoot_)) {
        Logger::log(LogLevel::ERROR, "Failed to load configuration file: " + configFile_);
        return false;
    }
    Logger::log(LogLevel::INFO, "Configuration file loaded successfully.");
    return true;
}

// Accessors for retrieving configuration settings

int ConfigurationLoader::getLoggingLevel() const {
    return JSONParser::getValueOrDefault(configRoot_["logging"], "level", 2);
}

double ConfigurationLoader::getMaxOrderAmount() const {
    return JSONParser::getValueOrDefault(configRoot_["risk"], "maxOrderAmount", 1000000.0);
}

double ConfigurationLoader::getMaxPosition() const {
    return JSONParser::getValueOrDefault(configRoot_["risk"], "maxPosition", 5000000.0);
}

double ConfigurationLoader::getMaxDailyLoss() const {
    return JSONParser::getValueOrDefault(configRoot_["risk"], "maxDailyLoss", 50000.0);
}

std::string ConfigurationLoader::getServerHost() const {
    return JSONParser::getValueOrDefault(configRoot_["connection"], "host", "localhost");
}

std::string ConfigurationLoader::getServerPort() const {
    return JSONParser::getValueOrDefault(configRoot_["connection"], "port", "5000");
}

int ConfigurationLoader::getHeartbeatInterval() const {
    return JSONParser::getValueOrDefault(configRoot_["connection"], "heartbeatInterval", 30);
}

int ConfigurationLoader::getMaxOrdersPerMinute() const {
    return JSONParser::getValueOrDefault(configRoot_["rateLimiter"], "maxOrdersPerMinute", 60);
}
