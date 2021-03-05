//
// Created by Nikolay Fedotenko on 03.03.2021.
//

#include "BaseWorker.h"

#include <unistd.h>
#include <pthread.h>

BaseWorker::BaseWorker()
    : _coordOnPoint(5), _steps(10), _currentInterval(0), _stopPush(false), points()
{
    for (size_t i = 0; i < STEPS_INTERVAL; ++i)
        points[i] = 0;
}

void BaseWorker::initializeShaderData()
{
    _countGridPoints = (_steps + 1) * 4;
    GLsizeiptr size = (_countGridPoints + STEPS_INTERVAL) * _coordOnPoint * sizeof(GLfloat);
    auto* vertices = new GLfloat[(_countGridPoints + STEPS_INTERVAL) * _coordOnPoint]();

    GLfloat gridColor[3] =
            {
                    217.0 / 0xff, 234.0 / 0xff, 244.0 / 0xff
            };

    bool direction = false;

    for (int i = 0, k = 0; i < _countGridPoints; i += 2, k += 2)
    {
        if (k % ((_steps + 1) * 2) == 0)
            k = 0;

        if ((int)(i / ((_steps + 1) * 2)) == 0 )
        {
            vertices[i * _coordOnPoint] = _area.left + (_area.width / _steps) * (int)(i / 2);
            vertices[(i + (int)direction) * _coordOnPoint + 1] = _area.top + _area.height;

            vertices[(i + 1) * _coordOnPoint] = _area.left + (_area.width / _steps) * (int)((i + 1) / 2);
            vertices[(i + (int)(!direction)) * _coordOnPoint + 1] = _area.top;
        }
        else
        {
            vertices[(i + (int)(direction)) * _coordOnPoint] = _area.left;
            vertices[i * _coordOnPoint + 1] = _area.top + (_area.height / _steps) * (int)(k / 2);

            vertices[(i + (int)(!direction)) * _coordOnPoint] = _area.left + _area.width;
            vertices[(i + 1) * _coordOnPoint + 1] = _area.top + (_area.height / _steps) * (int)((k + 1) / 2);
        }

        vertices[i * _coordOnPoint + 2] = gridColor[0];
        vertices[i * _coordOnPoint + 3] = gridColor[1];
        vertices[i * _coordOnPoint + 4] = gridColor[2];

        vertices[(i + 1) * _coordOnPoint + 2] = gridColor[0];
        vertices[(i + 1) * _coordOnPoint + 3] = gridColor[1];
        vertices[(i + 1) * _coordOnPoint + 4] = gridColor[2];

        direction = !direction;
    }

    for (size_t i = 0; i < STEPS_INTERVAL; ++i)
    {
        vertices[(_countGridPoints + i) * _coordOnPoint] = _area.left + (_area.width / (STEPS_INTERVAL - 1)) * i;
        vertices[(_countGridPoints + i) * _coordOnPoint + 4] = 0.0f;
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STREAM_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, _coordOnPoint * sizeof(GLfloat), (GLvoid*)nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, _coordOnPoint * sizeof(GLfloat), (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void BaseWorker::draw(Shader* shader)
{
    update();

    shader->Use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_STRIP, 0, _countGridPoints);
    glDrawArrays(GL_LINE_STRIP, _countGridPoints, _currentInterval);
    glBindVertexArray(0);
    glUseProgram(0);
}

void BaseWorker::update()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    auto* mapBuffer = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (size_t i = 0; i < _currentInterval; ++i)
    {
        mapBuffer[(i + _countGridPoints) * _coordOnPoint + 1] = _area.top + (1.0f - (points[i]) / 100.0f) * _area.height;
        mapBuffer[(i + _countGridPoints) * _coordOnPoint + 2] = points[i] / 100.0f;
        mapBuffer[(i + _countGridPoints) * _coordOnPoint + 3] = 1.0f - points[i] / 100.0f;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void* BaseWorker::staticThreadStart(void* Param)
{
    auto* This = (BaseWorker*)Param;
    This->threadStart();
}

[[noreturn]] void BaseWorker::threadStart()
{
    while (true)
    {
        if (!_stopPush)
            _currentInterval++;

        if (_currentInterval > STEPS_INTERVAL - 1)
        {
            for (size_t i = 1; i < STEPS_INTERVAL; ++i)
                points[i - 1] = points[i];

            _stopPush = true;
        }

        points[_currentInterval - 1] = getCurrentValue();

        usleep(500000);
    }
}

void BaseWorker::start()
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, staticThreadStart, (void*)this);
}
