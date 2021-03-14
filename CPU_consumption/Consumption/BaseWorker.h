//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include "../Utilities/Container.h"
#include "../Shader/Shader.h"

/*! \file
 *  This header declares BaseWorker class
 */

/*! \class
 *  Abstract base class for displaying graphs
 */
class BaseWorker
{
public:
    /*! \struct
     *  Rectangle structure for a graph
     */
    struct Rect
    {
        double width, height, left, top;
    };

    /*! \brief
     *  Default constructor
     */
    BaseWorker();

    /*! \brief
     *  Method to display graphs
     *  \param Pointer to the object of Shader class
     */
    void draw(Shader*);

    /*! \brief
     *  Inits and runs pthreads
     */
    void start();

    /*! \brief
     *  Pure virtual method to get current value of CPU consumption
     *  \return CPU load percentage
     */
    virtual double getCurrentValue() = 0;

private:
    int  _countGridPoints;
    int  _coordOnPoint;
    int  _steps;
    int  _currentInterval;
    bool _stopPush;

    GLuint VBO;
    GLuint VAO;

    Container<double, STEPS_INTERVAL> _points;

    /*! \brief
     *  Helper method for draw function to update info
     */
    void update();

    /*! \brief
     *  Helper methods to call start function
     */
    static void* staticThreadStart(void*);
    [[noreturn]] void threadStart();

protected:
    Rect _area;

    /*! \brief
     *  Helper method to initialize shader data
     */
    void initializeShaderData();
};

