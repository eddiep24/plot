#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#define __gl_h_
#define GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

#include <GLFW/glfw3.h>
#include </opt/homebrew/include/GL/glut.h>
#include </opt/homebrew/include/GL/gl.h>


#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>



#include "logs.h"
#include "shader_utils.h"
#include "math_utils.h"
#include "utils.h"


const size_t WIDTH = 500;
const size_t HEIGHT = 500;
const char *WINDOW_NAME = "Fick's Law";



/*
 * Callback to handle the "reload" event, once the user pressed the 'r' key.
 */
static void reloadShaders(GLFWwindow *window, int key, int scancode, int action, int _mods)
{
    if (key == GLFW_KEY_R && action == GLFW_PRESS)
    {
        debug("reloading...");
        loadShaderProgram(true);
    }
}


GLFWwindow *initializeWindow()
{
    // Minimum target is OpenGL 4.1
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(HEIGHT, WIDTH, WINDOW_NAME, NULL, NULL);
    if (!window)
    {
        error("window creation failed");
        return NULL;
    }
    // Easy reload
    glfwSetKeyCallback(window, reloadShaders);
    // Makes the window context current
    glfwMakeContextCurrent(window);
    // Enable the viewport
    glViewport(0, 0, HEIGHT, WIDTH);

    return window;
}





void drawAxes() {
    
}

void drawSquares() {


}


int main(void)
{
    // Initialize the lib
    if (!glfwInit())
    {
        error("could not start GLFW3");
        return -1;
    }

    GLFWwindow *window = initializeWindow();
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Note: Once you have a current OpenGL context, you can use OpenGL normally
    // get version info
    const GLubyte *renderer = glGetString(GL_RENDERER);
    const GLubyte *version = glGetString(GL_VERSION);
    info("Renderer: " << renderer);
    info("OpenGL version supported: " << version);

    if (!loadShaderProgram(false))
    {
        error("can't load the shaders to initiate the program");
        glfwTerminate();
        return -1;
    }

    float pos[] {
        -.5f, -.5f,
        0.0f, 0.5f,
        0.5f, -.5f
    };

    GLuint VBO = {};
    glGenBuffers(1, &VBO);

    

    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0, 0, 0, 1.0); // Set background color

        glClear(GL_COLOR_BUFFER_BIT); 
        // glUseProgram(shader_utils.getProgram().value());
        // glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        

        // Listen for events
        glfwPollEvents();
        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    glDeleteBuffers(1, &VBO);
    glfwTerminate();
    return 0;
}
