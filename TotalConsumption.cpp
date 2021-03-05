//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#include "TotalConsumption.h"

#include <mach/mach.h>

TotalConsumption::TotalConsumption(const struct Rect& currentArea)
    : _previousIdleTicks(0), _previousTotalTicks(0)
{
    _area = currentArea;

    initializeShaderData();
}

float TotalConsumption::calculate(unsigned long long idleTicks,
                                  unsigned long long totalTicks)
{
    unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
    unsigned long long idleTicksSinceLastTime  = idleTicks  - _previousIdleTicks;
    float ans = 1.0f -
                (totalTicksSinceLastTime > 0 ?
                static_cast<float>(idleTicksSinceLastTime) / totalTicksSinceLastTime :
                0);
    _previousTotalTicks = totalTicks;
    _previousIdleTicks  = idleTicks;
    return ans * 100;
}

double TotalConsumption::getCurrentValue()
{
    host_cpu_load_info_data_t cpuInfo;
    mach_msg_type_number_t count = HOST_CPU_LOAD_INFO_COUNT;
    if (host_statistics(mach_host_self(), HOST_CPU_LOAD_INFO, (host_info_t)&cpuInfo, &count) == KERN_SUCCESS)
    {
        unsigned long long totalTicks = 0;
        for (unsigned cpu_tick : cpuInfo.cpu_ticks)
            totalTicks += cpu_tick;
        return calculate(cpuInfo.cpu_ticks[CPU_STATE_IDLE], totalTicks);
    }
    else
        return -1.0f;
}
