#include "OrderRateLimiter.h"

OrderRateLimiter::OrderRateLimiter(size_t maxOrdersPerMinute)
    : maxOrdersPerMinute_(maxOrdersPerMinute) {}

bool OrderRateLimiter::canSendOrder() {
    auto now = std::chrono::steady_clock::now();
    while (!timestamps_.empty() && std::chrono::duration_cast<std::chrono::minutes>(now - timestamps_.front()).count() >= 1) {
        timestamps_.pop_front();
    }

    if (timestamps_.size() < maxOrdersPerMinute_) {
        timestamps_.push_back(now);
        return true;
    }
    Logger::log(LogLevel::WARNING, "Order rate limit exceeded.");
    return false;
}
