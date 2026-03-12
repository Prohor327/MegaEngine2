#include "ErrorChecker.h"
#include "Enums.h"
#include <iostream>
#include <glad/glad.h>

void ErrorLog(const char *text)
{
    std::cerr << "ERROR::" << text << "\n- --------------------------------------------------- -\n";
}

void CheckError(bool success, const Error::ErrorType& type)
{
    if(!success)
    {
        switch (type)
        {
        case Error::INITIALIZATION_GLFW:
            ErrorLog("GLFW_INITIALIZATION");
            break;
        case Error::CREATE_WINDOW:
            ErrorLog("CREATE_WINDOW");
            break;
        case Error::LOAD_GLAD:
            ErrorLog("LOAD_GLAD");
            break;
        default:
            break;
        }

    }
}