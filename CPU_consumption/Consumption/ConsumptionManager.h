//
// Created by Nikolay Fedotenko on 15.03.2021.
//

#pragma once

#include "TotalConsumption.h"
#include "CoresConsumption.h"

/*! \file
 *  This header declares ConsumptionManager class
 */

#include <thread>

#include <GLFW/glfw3.h>

/*! \class
 *  Manager class to display all info about CPU consumption
 */
class ConsumptionManager
{
public:
    /*! \brief
     *  Default constructor
     *
     *  Fills CPU consumption arrays and sets some OpenGL data for later drawing
     */
    ConsumptionManager();

    /*! \brief
     *  Destructor
     */
    ~ConsumptionManager();

    /*! \brief
     *  Draws all info
     */
    void draw();

private:
    TotalConsumption*  graph;
    CoresConsumption** graph2;
    unsigned           numCPU;
    Shader*            shader;
    float              projectionMatrix[16];

    /*! \brief
     *  Helper method to make orthogonal 2D matrix projection
     *  \param Projection matrix
     *
     *  \note Required in init method
     */
    static float* calculateOrtho2dProjection(float*);
};
