//
// Created by Nikolay Fedotenko on 15.03.2021.
//

#include "ConsumptionManager.h"

/*! \file
 *  This source defines ConsumptionManager class
 */

void ConsumptionManager::ortho2dProjection(float* mat)
{
    // this is basically from
    const float zNear = -1.0f;
    const float zFar = 1.0f;
    const float inv_z = 1.0f / (zFar - zNear);
    const float inv_y = -1.0f / HEIGHT;
    const float inv_x = 1.0f / WIDTH;

    //first column
    *mat++ = 2.0f * inv_x;
    *mat++ = 0.0f;
    *mat++ = 0.0f;
    *mat++ = 0.0f;

    //second
    *mat++ = 0.0f;
    *mat++ = 2.0f * inv_y;
    *mat++ = 0.0f;
    *mat++ = 0.0f;

    //third
    *mat++ = 0.0f;
    *mat++ = 0.0f;
    *mat++ = -2.0f * inv_z;
    *mat++ = 0.0f;

    //fourth
    *mat++ = -WIDTH * inv_x;
    *mat++ = -HEIGHT * inv_y;
    *mat++ = -(zFar + zNear) * inv_z;
    *mat = 1.0f;
}

void ConsumptionManager::init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);

    ortho2dProjection(projectionMatrix);

    shader = new Shader(projectionMatrix);

    graph = new TotalConsumption({ 100, 100, 10, 10 });
    graph->start();

    numCPU = std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 1;

    graph2 = new CoresConsumption*[numCPU];

    for (int i = 0; i < numCPU; ++i)
    {
        graph2[i] = new CoresConsumption( i, {50, 50, (double)(120 + i % 2 * 60),
                                              (double)(i / 2 * 70 + 10)} );
        graph2[i]->start();
    }
}

void ConsumptionManager::draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glPointSize(3.0);

    graph->draw(shader);

    for (size_t i = 0; i < numCPU; ++i)
        graph2[i]->draw(shader);

    glFlush();
}