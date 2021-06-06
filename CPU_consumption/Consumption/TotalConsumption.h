//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include "BaseWorker.h"

/*! \file
 *  This header declares TotalConsumption class
 */

/*! \class
 *  Derived class from BaseWorker to calculate total CPU consumption
 */
class TotalConsumption : public BaseWorker
{
public:
    /*! \brief
     *  Parameterized constuctor
     *  \param Size of graph
     */
    explicit TotalConsumption(const struct Rect&);

    /*! \brief
     *  Override method to get current value of total CPU consumption
     *  \return Total CPU load percentage
     */
    double getCurrentValue() override;

private:
    unsigned long long _previousTotalTicks;
    unsigned long long _previousIdleTicks;

    /*! \brief
     *  Helper method to calculate total CPU consumption (in %)
     *  \param Idle CPU ticks
     *  \param Total CPU ticks
     *  \return Total CPU load percentage
     */
    float calculate(unsigned long long,
                    unsigned long long);
};
