/*
 * © 2026 ZED Interactive. All Rights Reserved.
 */

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <cstdio>

#define TITLE "GL Renderer"
#define WIDTH 1280
#define HEIGHT 720

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

int main()
{
    // First init glfw then setup window hints which config glfw
    // the first arg is the option to set and the second arg is the
    // value of the option normally an int
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // This window hint is needed for Mac
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window obj
    GLFWwindow* window;
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    if (window == nullptr)
    {
        printf("Failed to create GLFW window.\n");
        glfwTerminate();
        return -1;
    }
    // Tell glfw to make the context of the window,
    // the main context on the current thread
    glfwMakeContextCurrent(window);

    // Glad 2 version, the og glad version would be:
    // (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    // Glad needs to be initialized before we can use modern opengl
    // Pass in the function to load OpenGL func pointers to glad,
    // this is OS specific however glfw handles it for us
    if (!gladLoadGL(glfwGetProcAddress))
    {
        printf("Failed to initialize GLAD.\n");
        return -1;
    }

    // Before we can render we need to tell opengl the size,
    // of the rendering window
    // The first 2 parms set the location of the lower left corner,
    // of the window and the last 2 are the width and height of the window
    glViewport(0, 0, WIDTH, HEIGHT);

    // Pass window resize callback to glfw so we can call it
    glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

    // Checks if the window should close at the start of the loop,
    // each iteration
    while (!glfwWindowShouldClose(window))
    {
        ProcessInput(window);

        // Render cmds go here
        // Specify the color to clear screen with
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Clears the screen and sets the color as chosen above
        glClear(GL_COLOR_BUFFER_BIT);

        // Swap back buffer with front buffer to render a frame
        glfwSwapBuffers(window);
        // Check if any events are triggered, update window state,
        // and call any callback funcs
        glfwPollEvents();
    }

    // Clean up window resources and properly exit
    glfwTerminate();
    return 0;
}

// Reg a callback func that resizes the window
void FrameBufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void ProcessInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}