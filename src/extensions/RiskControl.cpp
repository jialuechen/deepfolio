#include "RiskControl.h"

bool RiskControl::checkOrderLimits(double orderAmount) {
    if (orderAmount > maxOrderAmount_) {
        Logger::log(LogLevel::ERROR, "Order exceeds max limit.");
        return false;
    }
    return true;
}

void RiskControl::updatePosition(double amount) {
    currentPosition_ += amount;
    if (currentPosition_ > maxPosition_) {
        Logger::log(LogLevel::ERROR, "Position exceeds max limit.");
    }
}

bool RiskControl::checkDailyLossLimit(double orderLoss) {
    dailyLoss_ += orderLoss;
    if (dailyLoss_ > maxDailyLoss_) {
        Logger::log(LogLevel::ERROR, "Daily loss limit exceeded.");
        return false;
    }
    return true;
}
