
#include "example.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

const glm::vec2 SCREEN_SIZE(1024, 768);

int main(int argc, char** argv)
{

    GLFWwindow* gWindow;
    
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    
    gWindow = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "Terrain Example", NULL, NULL);
    if(!gWindow)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
    glfwMakeContextCurrent(gWindow);

    //The example OpenGL code
    Example example;

    

    if (!example.init()) //Initialize our example
    {
        return 1;
    }

    float lastTime = glfwGetTime();
    //This is the mainloop, we render frames until isRunning returns false
    while(!glfwWindowShouldClose(gWindow))
    {
        glfwPollEvents();
        
        float thisTime = glfwGetTime();
        lastTime = thisTime;
        
        example.prepare(thisTime - lastTime ); //Do any pre-rendering logic
        example.render(); //Render the scene

        if(glfwGetKey(gWindow, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(gWindow, GL_TRUE);
    }
    
    //this does nothing
    example.shutdown(); //Free any resources
    
    glfwTerminate();
    
    return 0; //Return success
}
