//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

/*! \file
 *  This header declares Shader class
 */

#include <GL/glew.h>

#include "../Utilities/Constants.h"

/*! \class
 *  Wrapper class for using GLSL shaders
 */
class Shader
{
public:
    /*! \brief
     *  Parameterized constructor
     *  \param Projection matrix
     */
    explicit Shader(GLfloat*);

    /*! \brief
     *  Constant method to call glUseProgram and glUniformMatrix4fv
     */
    void use() const;

private:
    GLuint   _program;
    GLfloat* _projectionMatrix;
};

