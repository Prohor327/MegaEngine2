#include "Core.h"
#include "Renderer/Shader.h"
#include "Tools/ErrorChecker.h"
#include "Tools/Enums.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <time.h>
#include <glad/glad.h>
#include <string>

namespace Core 
{

    GLFWwindow* window;
    GLFWmonitor* monitor;
    int frameCount;
    float deltaTime;
    double previousTime;
    float startFrame;


    void initalize()
    {
        CheckError((bool)glfwInit(), Error::INITIALIZATION_GLFW);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        glfwSetErrorCallback(errorCallback);

        monitor = glfwGetPrimaryMonitor();
        window = glfwCreateWindow(1100, 800, "window", NULL, NULL);

        CheckError((bool)window, Error::CREATE_WINDOW);
        glfwSwapInterval(1);

        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

        CheckError((bool)gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), Error::LOAD_GLAD);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }

    void beginFrame()
    {
        startFrame = static_cast<float>(glfwGetTime());
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void endFrame()
    {
        float endFrame = static_cast<float>(glfwGetTime());
        deltaTime = endFrame - startFrame;
        if (deltaTime > 0.033f)
        {
            deltaTime = 0.033f;
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    void cleanUp()
    {
        glfwTerminate();
    }
    
    GLFWwindow* getWindow()
    {
        return window;
    }
    
    bool windowIsOpen()
    {
        return glfwWindowShouldClose(window);
    }

    float* getDeltaTimePtr()
    {
        return &deltaTime;
    }

    float getDeltaTime()
    {
        return deltaTime;
    }

    void framebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void errorCallback(int error_code, const char *description)
    {
        std::cout << description << "error code: " << error_code << std::endl;
    }

    void setWindowTitle(std::string title)
    {
        glfwSetWindowTitle(window, title.c_str());
    }
    
    void setWindowSize(int width, int heigth)
    {
        glfwSetWindowSize(window, width, heigth);
    }

    int getWindowedWidth()
    {
        int width;
        glfwGetWindowSize(window, &width, nullptr);
        return width;
    }

    int getWindowedHeight()
    {
        int height;
        glfwGetWindowSize(window, nullptr, &height);
        return height;
    }
}