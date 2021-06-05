cmake_minimum_required(VERSION 3.14)
PROJECT(CPU_consumption)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-target arm64-apple-macos11 -framework Cocoa -framework IOKit -framework OpenGL")

set(GLEW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdParties/glew/2.2.0_1/include")
set(GLFW_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/3rdParties/glfw/3.3.3/include")
set(INCLUDE_DIRS     ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR})

set(GLEW_LIBRARY     "${PROJECT_SOURCE_DIR}/3rdParties/glew/2.2.0_1/lib/libGLEW.a")
set(GLFW_LIBRARY     "${PROJECT_SOURCE_DIR}/3rdParties/glfw/3.3.3/lib/libglfw3.a")
set(LIBRARIES        ${GLEW_LIBRARY} ${GLFW_LIBRARY})

add_executable(CPU_consumption
               main.cpp
               CPU_consumption/Utilities/Constants.h
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

include_directories(${INCLUDE_DIRS})

target_link_libraries(CPU_consumption ${LIBRARIES})
