#include "FIXParser.h"
#include <sstream>

FIXParser::FIXParser() {}

bool FIXParser::parseMessage(const std::string_view& message) {
    fields_.clear();
    size_t pos = 0;
    while (pos < message.size()) {
        auto key_end = message.find('=', pos);
        if (key_end == std::string_view::npos) return false;
        
        auto key = message.substr(pos, key_end - pos);
        pos = key_end + 1;
        
        auto value_end = message.find('|', pos);
        if (value_end == std::string_view::npos) return false;
        
        auto value = message.substr(pos, value_end - pos);
        pos = value_end + 1;
        
        fields_[key] = value;
    }
    return true;
}

template<typename T>
T FIXParser::getFieldAs(const std::string& tag) const {
    std::stringstream ss(std::string(getField(tag)));
    T value;
    ss >> value;
    return value;
}

std::string_view FIXParser::getField(const std::string& tag) const {
    auto it = fields_.find(tag);
    return it != fields_.end() ? it->second : "";
}

std::string FIXParser::buildMessage(const std::unordered_map<std::string, std::string>& fields) {
    std::string message;
    for (const auto& [key, value] : fields) {
        message += key + "=" + value + "|";
    }
    return message;
}
