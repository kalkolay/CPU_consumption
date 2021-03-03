cmake_minimum_required(VERSION 3.14)
PROJECT(CPU_consumption)

set(CMAKE_CXX_STANDARD 17)

add_executable(CPU_consumption
        main.cpp
        Constants.h
        Shader.cpp
        Shader.h BaseWorker.cpp BaseWorker.h TotalConsumption.cpp TotalConsumption.h CoresConsumption.cpp CoresConsumption.h)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

target_link_libraries(CPU_consumption OpenGL::GL glfw GLEW::glew)