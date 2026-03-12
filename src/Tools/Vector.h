#pragma once

#include <glm/vec3.hpp>

namespace vector
{
    const glm::vec3 forward(0.0f, 0.0f, 1.0f);
    const glm::vec3 up(0.0f, 1.0f, 0.0f);
    const glm::vec3 right(1.0f, 0.0f, 0.0f);
    const glm::vec3 left(-1.0f, 0.0f, 0.0f);
    const glm::vec3 back(0.0f, 0.0f, -1.0f);
    const glm::vec3 zero = glm::vec3(0.0f);
    const glm::vec3 one = glm::vec3(1.0f);
}