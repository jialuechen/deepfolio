#ifndef CONFIGURATIONLOADER_H
#define CONFIGURATIONLOADER_H

#include <json/json.h>
#include <string>
#include <iostream>
#include "Logger.h"
#include "JSONParser.h"

class ConfigurationLoader {
public:
    // Constructor that loads configuration from a specified file
    ConfigurationLoader(const std::string& configFile = "config/config.json");

    // Loads the configuration file and parses it into Json::Value
    bool loadConfig();

    // Accessor functions to retrieve specific configuration settings
    int getLoggingLevel() const;
    double getMaxOrderAmount() const;
    double getMaxPosition() const;
    double getMaxDailyLoss() const;
    std::string getServerHost() const;
    std::string getServerPort() const;
    int getHeartbeatInterval() const;
    int getMaxOrdersPerMinute() const;

private:
    std::string configFile_;
    Json::Value configRoot_;
};

#endif // CONFIGURATIONLOADER_H
