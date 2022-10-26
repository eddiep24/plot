#ifdef __APPLE__
/* Defined before OpenGL and GLUT includes to avoid deprecation messages */
#define GL_SILENCE_DEPRECATION
#define GLFW_INCLUDE_GLCOREARB
#include <GLFW/glfw3.h>
// #else
//  #include <GL/gl.h>
// #include <GL/glut.h>
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>


#include "logs.h"
#include "shader_utils.h"
#include "math_utils.h"



const size_t WIDTH = 640;
const size_t HEIGHT = 480;
const char *WINDOW_NAME = "OpenGL Explorer";
auto shader_utils = ShaderUtils::Program{};


/**
 * @brief Load the shaders, in order to display the result
 *
 * @param erase_if_program_registered Allow to erase the shader if it exists
 * @return true The shader has been successfully registered
 * @return false The shader has not been registered, due to an error
 */
const bool loadShaderProgram(const bool erase_if_program_registered);

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

/*
 * Initializes the window and viewport via GLFW.
 * The viewport takes the all window.
 * If an error happens, the function returns `NULL` but **does not** free / terminate the GLFW library.
 * Then, do not forget to call `glfwTerminate` if this function returns `NULL`.
 */
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

/**
 * @brief Returns the all file, as a string, which the file path has been passed
 * as parameter
 *
 * @param path The path of the file
 * @return The content of the file, as a string (read all file)
 */
inline std::string readFile(const char* filePath) 
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);
	std::string line = "";
	while(!fileStream.eof())
	{
		getline(fileStream, line);
		content.append(line + "\n");
	}
	fileStream.close();
	return content;
}

const bool loadShaderProgram(const bool erase_if_program_registered = true)
{
    const std::string basicVertexShaderSource = readFile("../Shaders/vert.glsl");
    const std::string basicFragmentShaderSource = readFile("../Shaders/frag.glsl");
    // const char *basicVertexShaderSource = "#version 410 core\n"
    //                                     "layout (location = 0) in vec3 vertexPosition;\n"
    //                                     "layout (location = 1) in vec3 vertexColor;\n"
    //                                     "layout (location = 0) out vec3 fragmentColor;\n"
    //                                     "void main()\n"
    //                                     "{\n"
    //                                     "    gl_Position = vec4(vertexPosition, 1.0);\n"
    //                                     "    fragmentColor = vertexColor;\n"
    //                                     "}\0";

    // const char *basicFragmentShaderSource = "#version 410 core\n"
    //                                         "layout (location = 0) in vec3 fragmentColor;\n"
    //                                         "out vec4 finalColor;\n"
    //                                         "void main()\n"
    //                                         "{\n"
    //                                         "    finalColor = vec4(fragmentColor, 1.0);\n"
    //                                         "}\0";

    if (!shader_utils.registerShader(ShaderUtils::Type::VERTEX_SHADER_TYPE, basicVertexShaderSource.c_str()))
    {
        error("failed to register the vertex shader...");
        return false;
    }

    if (!shader_utils.registerShader(ShaderUtils::Type::FRAGMENT_SHADER_TYPE, basicFragmentShaderSource.c_str()))
    {
        error("failed to register the fragment shader...");
        return false;
    }

    if (!shader_utils.registerProgram(erase_if_program_registered))
    {
        error("failed to register the program...");
        return false;
    }
    return true;
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
    /* END OF SHADER PART */

    /* DRAW THE TRIANGLE */
    const MathUtils::vertex vertices[3] = {
        {0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f},
        {0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f},
        {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f}};

    // Vertex Buffer Object = VBO
    GLuint VBO = {};
    glGenBuffers(1, &VBO);

    // Something failed when generating buffers
    if (glGetError() != GL_NO_ERROR)
    {
        error("error when generating buffers");
        glDeleteBuffers(1, &VBO); // TODO: Needed?
        glfwTerminate();
        return -1;
    }
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, MathUtils::getNbElements(vertices) * sizeof(float), vertices, GL_STATIC_DRAW | GL_MAP_READ_BIT);

    // Vertex Arrays Object = VAO
    GLuint VAO = {};
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Specify position attribute -> 0 as offset
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, MathUtils::VERTEX_ELEMENTS_NB * sizeof(float), (GLvoid *)0);
    glEnableVertexAttribArray(0);

    // Specify color attribute -> 3 as offset
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, MathUtils::VERTEX_ELEMENTS_NB * sizeof(float), (GLvoid *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    /* END OF DRAWING */

    while (!glfwWindowShouldClose(window))
    {
        // Render
        glClearColor(0.5, 0.5, 0.5, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shader_utils.getProgram().value());
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // Poll for and process events
        glfwPollEvents();
        // Swap front and back buffers
        glfwSwapBuffers(window);
    }

    // ... here, the user closed the window
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
    glfwTerminate();
    return 0;
}
