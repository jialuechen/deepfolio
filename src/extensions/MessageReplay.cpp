#include "MessageReplay.h"
#include <algorithm>

MessageReplay::MessageReplay(size_t maxHistorySize)
    : maxHistorySize_(maxHistorySize) {}

// Records a message for a specific session, adding a sequence number
void MessageReplay::recordMessage(const std::string& sessionId, const std::string& message) {
    std::lock_guard<std::mutex> lock(mutex_);
    
    // Determine the next sequence number for this session
    int seqNum = messageHistory_[sessionId].empty() ? 1 : messageHistory_[sessionId].back().first + 1;
    
    // Add the new message to the history
    messageHistory_[sessionId].emplace_back(seqNum, message);

    // Ensure we don't exceed the max history size for this session
    if (messageHistory_[sessionId].size() > maxHistorySize_) {
        messageHistory_[sessionId].pop_front();
    }
}

// Retrieves messages starting from a given sequence number for a specific session
std::vector<std::string> MessageReplay::getMessagesSince(const std::string& sessionId, int startSeqNum) const {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<std::string> result;

    // Check if session exists in the history
    auto it = messageHistory_.find(sessionId);
    if (it == messageHistory_.end()) {
        return result; // Return empty vector if session does not exist
    }

    // Find and collect all messages with sequence numbers >= startSeqNum
    for (const auto& [seqNum, msg] : it->second) {
        if (seqNum >= startSeqNum) {
            result.push_back(msg);
        }
    }

    return result;
}

// Clears the message history for a specific session
void MessageReplay::clearSessionHistory(const std::string& sessionId) {
    std::lock_guard<std::mutex> lock(mutex_);
    messageHistory_.erase(sessionId);
}
