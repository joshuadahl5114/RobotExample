#ifndef _EXAMPLE_H
#define _EXAMPLE_H

#include <OpenGL/gl.h>
#include <vector>
#include "robot.h"

using std::vector;

class Example
{
public:
    Example();

    bool init();
    void prepare(float dt);
    void render();
    void shutdown();
    void project(int width, int height);
    void onResize(int width, int height);

private:
    Robot m_robot;
    GLfloat m_rotationAngle;
};

#endif
