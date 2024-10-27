#ifndef RISKCONTROL_H
#define RISKCONTROL_H

#include "Logger.h"

class RiskControl {
public:
    bool checkOrderLimits(double orderAmount);
    void updatePosition(double amount);
    bool checkDailyLossLimit(double orderLoss);

private:
    double maxOrderAmount_ = 1000000;
    double maxPosition_ = 5000000;
    double currentPosition_ = 0;
    double maxDailyLoss_ = 50000;
    double dailyLoss_ = 0;
};

#endif // RISKCONTROL_H
