#pragma once

#include <GLFW/glfw3.h>
#include <string>

namespace Core {

    void initalize();
    void beginFrame();
    void endFrame();
    void cleanUp();
    
    GLFWwindow* getWindow();
    void toggleFullscreen();
    bool windowIsOpen();
    int getWindowedWidth();
    int getWindowedHeight();
    unsigned int getShader();
    float getDeltaTime();
    void setWindowSize(int width, int heigth);

    void setWindowTitle(std::string title);

    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void errorCallback(int error_code, const char *description);
}