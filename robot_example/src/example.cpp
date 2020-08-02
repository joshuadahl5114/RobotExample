


#include <GL/gl.h>
#include <GL/glu.h>

#include "example.h"


Example::Example()
{
}

bool Example::init()
{
 
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDisable(GL_CULL_FACE);
    glClearColor(0.0f, 0.0f, 0.0f, 0.5f);

    bool result = m_robot.initialize();
    m_rotationAngle = 0.0f;
    //Return success
    return result;
}

void Example::prepare(float dt)
{
    m_rotationAngle += 10.0f * dt;
    if (m_rotationAngle > 360.0f) {
        m_rotationAngle -= 360.0f;
    }

    m_robot.animate(dt);
}

void Example::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    glLoadIdentity();
        
	glPushMatrix();							// put current matrix on stack
		glLoadIdentity();					// reset matrix
		glTranslatef(0.0f, 0.0f, -30.0f);	// move to (0, 0, -30)
		glRotatef(m_rotationAngle, 0.0f, 1.0f, 0.0f);	// rotate the robot on its y-axis
		m_robot.render(0.0f, 0.0f, 0.0f);
	glPopMatrix();		

    
}

void Example::project(int width, int height)
{
    //Prevent a divide by zero error
    if (height <= 0)
    {
        height = 1;
    }
    
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluPerspective(52.0f, float(width) / float(height), 1.0f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Example::shutdown()
{

}

void Example::onResize(int width, int height)
{
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(52.0f, float(width) / float(height), 1.0f, 1000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
