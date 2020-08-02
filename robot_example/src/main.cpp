
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "SDL/SDL.h"
#include <sys/time.h>
#include "example.h"
#include <string>

GLFWwindow* gWindow = NULL;
unsigned int m_lastTime;

void OnError(int errorCode, const char* msg) {
    throw std::runtime_error(msg);
}

static unsigned int GetTickCount() {
    struct timeval t;
    gettimeofday(&t, NULL);
    
    unsigned long secs = t.tv_sec * 1000;
    secs += (t.tv_usec / 1000);
    return secs;
}


static void useSDL(int width, int height)
{
    if ( SDL_Init( SDL_INIT_VIDEO ) != 0 )
    {
        // std::cerr << "Could not initialize SDL" << std::endl;
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    
    std::string title = "Robot Example";
    SDL_WM_SetCaption(title.c_str(), title.c_str());
    
    // Create the window
    if (!SDL_SetVideoMode(1024, 768, 0, SDL_OPENGL | SDL_RESIZABLE))
    {
        //std::cerr << "Could not create the window" << std::endl;
        return false;
    }
    
    Example *example = new Example();
    
    //initilize and bind VAO and VBO for the triangle
    // myApp.LoadTriangles();
    
    if (!example->init())
    {
        SDL_Quit();
        return 1;
    }
    
    bool done = false;
    //might not need that
    example->project(1024, 768);
    
    
    while (!done)
    {
        SDL_Event event;
        unsigned int currentTime = GetTickCount();
        unsigned int diff = currentTime - m_lastTime;
        double delta = diff / 700.0f;
        
        while (SDL_PollEvent(&event))
        {
            
            switch(event.type) {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_VIDEORESIZE:
                    example->onResize(event.resize.w, event.resize.h);
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        done = true;
                    }
                    break;
                default:
                    break;
            }
        }
        m_lastTime = currentTime;
        example->prepare(0.02f);
        example->render();
        // with shader not working
        // myApp.RenderScene();
        SDL_GL_SwapBuffers();
    }
    
    SDL_Quit();
}

static void useGLFW(int width, int height)
{
    glfwSetErrorCallback(OnError);
    if(!glfwInit())
        throw std::runtime_error("glfwInit failed");
    
    // open a window with GLFW
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    gWindow = glfwCreateWindow(width, height, "Robot Example", NULL, NULL);
    if(!gWindow)
        throw std::runtime_error("glfwCreateWindow failed. Can your hardware handle OpenGL 3.2?");
    
    glfwMakeContextCurrent(gWindow);
    
    // initialise GLEW
    glewExperimental = GL_TRUE; //stops glew crashing on OSX :-/
    if(glewInit() != GLEW_OK)
        throw std::runtime_error("glewInit failed");
    
    // GLEW throws some errors, so discard all the errors so far
    while(glGetError() != GL_NO_ERROR) {}
    
    //The example OpenGL code
    Example example;
    
    if (!example.init()) //Initialize our example
    {
        //throw an exception
        return 1;
    }
    
    example.project(width, height);
    
    double lastTime = glfwGetTime();
    //This is the mainloop, we render frames until isRunning returns false
    while(!glfwWindowShouldClose(gWindow))
    {
        glfwPollEvents();//Process any window events
        
        //We get the time that passed since the last frame
        float elapsedTime = glfwGetTime();
        
        example.prepare(elapsedTime); //Do any pre-rendering logic
        example.render(); //Render the scene
        
        if(glfwGetKey(gWindow, GLFW_KEY_ESCAPE))
            glfwSetWindowShouldClose(gWindow, GL_TRUE);
        
        glfwSwapBuffers(gWindow);
    }
    
    example.shutdown(); //Free any resources
    glfwTerminate();
}

int main(int argc, char** argv)
{
    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    
    useSDL(windowWidth, windowHeight);

    return 0; //Return success
}
