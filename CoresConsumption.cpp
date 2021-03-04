//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#include "CoresConsumption.h"

CoresConsumption::CoresConsumption(int n)
{
    mach_msg_type_number_t count;
    processor_info_array_t coreInfo;
    host_processor_info(mach_host_self(),
                        PROCESSOR_CPU_LOAD_INFO,
                        &_coreCount,
                        &coreInfo,
                        &count
    );

    _number = n;
    _cores = (core_info_t*)malloc(sizeof(core_info_t) * _coreCount);
}

CoresConsumption::~CoresConsumption()
{
    free(_cores);
}

double CoresConsumption::getCurrentValue()
{
    mach_msg_type_number_t count;
    processor_cpu_load_info_t coreInfo;
    natural_t user, system, idle, nice;
    double used, total;

    host_processor_info(mach_host_self(),
                        PROCESSOR_CPU_LOAD_INFO,
                        &_coreCount,
                        (processor_info_array_t*)&coreInfo,
                        &count
    );
    user = coreInfo[_number].cpu_ticks[CPU_STATE_USER] - _cores[_number].cpu_ticks[CPU_STATE_USER];
    system = coreInfo[_number].cpu_ticks[CPU_STATE_SYSTEM] - _cores[_number].cpu_ticks[CPU_STATE_SYSTEM];
    idle = coreInfo[_number].cpu_ticks[CPU_STATE_IDLE] - _cores[_number].cpu_ticks[CPU_STATE_IDLE];
    nice = coreInfo[_number].cpu_ticks[CPU_STATE_NICE] - _cores[_number].cpu_ticks[CPU_STATE_NICE];
    used = user + system + nice;
    total = system + user + idle + nice;
    _cores[_number].usage = used / total;
    _cores[_number].cpu_ticks[CPU_STATE_USER] = coreInfo[_number].cpu_ticks[CPU_STATE_USER];
    _cores[_number].cpu_ticks[CPU_STATE_SYSTEM] = coreInfo[_number].cpu_ticks[CPU_STATE_SYSTEM];
    _cores[_number].cpu_ticks[CPU_STATE_IDLE] = coreInfo[_number].cpu_ticks[CPU_STATE_IDLE];
    _cores[_number].cpu_ticks[CPU_STATE_NICE] = coreInfo[_number].cpu_ticks[CPU_STATE_NICE];

    return _cores[_number].usage > 1 ? 100 : _cores[_number].usage * 100;
}
