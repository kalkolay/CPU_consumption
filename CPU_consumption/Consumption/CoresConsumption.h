//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include "BaseWorker.h"

/*! \file
 *  This header declares CoresConsumption class
 */

#include <mach/mach.h>

/*! \class
 *  Derived class from BaseWorker to calculate CPU consumption per cores
 */
class CoresConsumption : public BaseWorker
{
    /*! \struct
     *  Info of a single core
     *
     *  \note Required to work with cores data properly via Mach API
     */
    typedef struct _core_info_t
    {
        natural_t cpu_ticks[CPU_STATE_MAX];
        double usage;
    } core_info_t;

public:
    /*! \brief
     *  Parameterized constructor
     *  \param Core number
     *  \param Size of graph
     */
    CoresConsumption(int,
                     const Rect&);
    /*! \brief
     *  Destructor
     */
    ~CoresConsumption();

    /*! \brief
     *  Override method to get current value of CPU consumption per core
     *  \return CPU load percentage for a certain core
     */
    double getCurrentValue() override;

private:
    unsigned     _coreCount;
    core_info_t* _cores;
    int          _number;
};
