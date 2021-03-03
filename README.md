# CPU consumption monitor

## Description

CPU consumption monitor is a multithread C++ desktop application with OpenGL API (GLFW/GLEW) on Mac OS. This project shows CPU load curves (total and by kernels). The UI (implemented via GLSL shaders version 330 core) is rather primitive and similar to Task Manager (standard Windows app). The curves use different colors depending on the degree of load (for example, the peak load range is red). CPU consumption data is taken from Mach API. *TODO: add description of each graph + screenshot*

## Implementation details

