#ifndef MESSAGEREPLAY_H
#define MESSAGEREPLAY_H

#include <deque>
#include <unordered_map>
#include <string>
#include <vector>
#include <mutex>

class MessageReplay {
public:
    // Constructor that sets the maximum number of messages to store per session
    explicit MessageReplay(size_t maxHistorySize = 1000);

    // Records a message for a specific session
    void recordMessage(const std::string& sessionId, const std::string& message);

    // Retrieves all messages starting from a given sequence number for a specific session
    std::vector<std::string> getMessagesSince(const std::string& sessionId, int startSeqNum) const;

    // Clears all stored messages for a specific session
    void clearSessionHistory(const std::string& sessionId);

private:
    size_t maxHistorySize_;  // Maximum number of messages to store per session
    mutable std::mutex mutex_;  // Mutex to ensure thread safety
    std::unordered_map<std::string, std::deque<std::pair<int, std::string>>> messageHistory_;  // Stores message history per session
};

#endif // MESSAGEREPLAY_H
