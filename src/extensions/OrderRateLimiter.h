#ifndef ORDER_RATE_LIMITER_H
#define ORDER_RATE_LIMITER_H

#include <chrono>
#include <deque>
#include "Logger.h"

class OrderRateLimiter {
public:
    OrderRateLimiter(size_t maxOrdersPerMinute);

    bool canSendOrder();

private:
    size_t maxOrdersPerMinute_;
    std::deque<std::chrono::steady_clock::time_point> timestamps_;
};

#endif // ORDER_RATE_LIMITER_H
