cmake_minimum_required(VERSION 3.14)
PROJECT(CPU_consumption)

set(CMAKE_CXX_STANDARD 17)

set(glfw3_DIR ${CMAKE_SOURCE_DIR/3rdParties/glfw})
set(GLEW_DIR ${CMAKE_SOURCE_DIR/3rdParties/glew})

add_executable(CPU_consumption
               main.cpp
               CPU_consumption/Utilities/Constants.h
               CPU_consumption/Utilities/Container.h
               CPU_consumption/Shader/Shader.cpp
               CPU_consumption/Shader/Shader.h
               CPU_consumption/Consumption/BaseWorker.cpp
               CPU_consumption/Consumption/BaseWorker.h
               CPU_consumption/Consumption/TotalConsumption.cpp
               CPU_consumption/Consumption/TotalConsumption.h
               CPU_consumption/Consumption/CoresConsumption.cpp
               CPU_consumption/Consumption/CoresConsumption.h
               CPU_consumption/Consumption/ConsumptionManager.cpp
               CPU_consumption/Consumption/ConsumptionManager.h)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(CPU_consumption glfw GLEW::glew)