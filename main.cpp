//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#include "TotalConsumption.h"
#include "CoresConsumption.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    CoresConsumption** coresConsumption;
    unsigned numCPU = std::thread::hardware_concurrency();
    coresConsumption = new CoresConsumption*[numCPU];

    while (true)
    {
        std::cout << "====================\n";
        auto* totalConsumption = new TotalConsumption();
        std::cout << "Total: " << totalConsumption->getCurrentValue() << std::endl;
        for (unsigned i = 0; i < numCPU; ++i)
        {
            std::cout << "Core " << i + 1;
            coresConsumption[i] = new CoresConsumption(i);
            std::cout << coresConsumption[i]->getCurrentValue() << std::endl;
        }
        std::this_thread::sleep_for( std::chrono::seconds(1) );
    }

    return 0;
}