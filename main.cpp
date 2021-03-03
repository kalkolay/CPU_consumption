//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#include "TotalConsumption.h"

#include <GLFW/glfw3.h>

#include <iostream>
#include <chrono>
#include <thread>

int main()
{
    TotalConsumption test;
    while (true)
    {
        std::cout << test.getCurrentValue() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    return 0;
}