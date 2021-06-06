//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include "../Utilities/Constants.h"
#include "../Shader/Shader.h"

/*! \file
 *  This header declares BaseWorker class
 */

#include <array>

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
    void drawCurve(Shader *shader);

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
    int  _currentInterval;
    bool _stopPush;        // Indicates when we have to stop incrementing _currentInterval

    const int _coordOnPoint = 5;   // Coefficient for displaying points
    const int _steps        = 10;  // Number of cells on both horizontal and vertical sides of the graph

    /*! \brief
     *  Vertex array & buffer objects.
     *
     *  \see https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Array_Object
     *  \see https://www.khronos.org/opengl/wiki/Vertex_Specification#Vertex_Buffer_Object
     */
    GLuint VBO;
    GLuint VAO;

    std::array<double, STEPS_INTERVAL> _points;

    /*! \brief
     *  Helper method for filling the vertices array
     */
    inline void fillVertices(GLfloat*, int);

    /*! \brief
     *  Helper method for drawCurve function to update info
     */
    void update();

    /*! \brief
     *  Helper methods to call start function
     */
    static void* threadStartStatic(void*);
    [[noreturn]] void threadStart();

protected:
    Rect _area;

    /*! \brief
     *  Helper method to initialize shader data
     */
    void initializeShaderData();
};
