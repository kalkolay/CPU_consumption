# CPU consumption monitor

[![Build](https://github.com/kalkolay/CPU_consumption/actions/workflows/macos-cmake-build.yml/badge.svg)](https://github.com/kalkolay/CPU_consumption/actions/workflows/macos-cmake-build.yml)

## Description

CPU consumption monitor is a C++ desktop application with OpenGL API (GLFW/GLEW) on Mac OS. This project shows CPU load curves (total and by cores). The UI, which is implemented via shaders, is rather primitive and similar to Task Manager (default Windows application).

Sample usage:\
<a href="https://ibb.co/BywtRKW"><img src="https://i.ibb.co/2v5yBYV/demonstration.png" alt="demonstration" border="0" /></a>

You can see total CPU consumption on the left and CPU consumption per each core on the right (cores are displayed from left to right). 

## Functional features
- The curves use different colors depending on the degree of load (for example, the peak load range is red);
- A self-written container is used to store the graphs data;
- Memory for the curves data is allocated once during the launch of the application;
- Each curve is updated in a separate thread (including the general one). Threads are also created once by means of the operating system when the application is launched;
- The class that updates a specific curve inherits from the base Worker interface;
- The CPU consumption data is taken from Mach API;
- Shaders are written on GLSL (version 330 core).

Built using C++17 standard but may be also built on C++11, C++14 and C++20.

## License

CPU consumption monitor is licensed under the [MIT License](https://github.com/kalkolay/CPU_consumption/blob/main/LICENSE)
