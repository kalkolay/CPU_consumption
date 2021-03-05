//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include "BaseWorker.h"

class TotalConsumption : public BaseWorker
{
public:
    TotalConsumption(const struct Rect&);
    double getCurrentValue() override;

private:
    unsigned long long _previousTotalTicks;
    unsigned long long _previousIdleTicks;

    float calculate(unsigned long long, unsigned long long);
};
