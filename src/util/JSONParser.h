#ifndef JSONPARSER_H
#define JSONPARSER_H

#include <json/json.h>
#include <fstream>
#include <string>
#include <iostream>

class JSONParser {
public:
    // Loads and parses a JSON file, returning a Json::Value root
    static bool loadJSON(const std::string& filename, Json::Value& root) {
        std::ifstream file(filename, std::ifstream::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open JSON file " << filename << std::endl;
            return false;
        }

        Json::CharReaderBuilder readerBuilder;
        std::string errs;
        bool parsingSuccessful = Json::parseFromStream(readerBuilder, file, &root, &errs);
        if (!parsingSuccessful) {
            std::cerr << "Error: Failed to parse JSON file " << filename << "\n" << errs << std::endl;
        }
        return parsingSuccessful;
    }

    // Retrieves a value from the JSON root, returning a default if the key is missing
    template <typename T>
    static T getValueOrDefault(const Json::Value& root, const std::string& key, const T& defaultValue) {
        return root.isMember(key) ? root[key].as<T>() : defaultValue;
    }
};

#endif // JSONPARSER_H
