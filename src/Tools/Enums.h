#pragma once

namespace Error
{
    enum ErrorType
    {
        INITIALIZATION_GLFW = 1,
        CREATE_WINDOW = 2,
        LOAD_GLAD = 3,
        COMPILE_SHADER = 4,
        LINK_PROGRAM = 5
    };
}