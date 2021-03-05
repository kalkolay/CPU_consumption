//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include "Container.h"
#include "Shader.h"

#include <string>

class BaseWorker
{
public:
    struct Rect
    {
        double width, height, left, top;
    };

    BaseWorker();
    void draw(Shader*);
    void start();
    static void* staticThreadStart(void*);

    [[noreturn]] void threadStart();
    virtual double getCurrentValue() = 0;

private:
    int _countGridPoints;
    int _coordOnPoint;
    int _steps;
    int _currentInterval;
    bool _stopPush;
    GLuint VBO;
    GLuint VAO;
    void update();
    Container<double, STEPS_INTERVAL> points;

protected:
    Rect _area;

    void initializeShaderData();
};

