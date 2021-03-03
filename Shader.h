//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#pragma once

#include <GL/glew.h>

#include "Constants.h"

class Shader
{
public:
    Shader(GLfloat*);

    void Use() const;

private:
    GLuint   _program;
    GLfloat* _projectionMatrix;
};

