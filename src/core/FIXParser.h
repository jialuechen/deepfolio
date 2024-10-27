#ifndef FIXPARSER_H
#define FIXPARSER_H

#include <unordered_map>
#include <string_view>
#include <string>

class FIXParser {
public:
    explicit FIXParser();
    
    bool parseMessage(const std::string_view& message);
    
    template<typename T>
    T getFieldAs(const std::string& tag) const;

    std::string_view getField(const std::string& tag) const;
    
    std::string buildMessage(const std::unordered_map<std::string, std::string>& fields);

private:
    std::unordered_map<std::string_view, std::string_view> fields_;
};

#endif // FIXPARSER_H
