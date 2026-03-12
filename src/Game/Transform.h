#pragma once

#include <Tools/Vector.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Transform
{
    glm::vec3 position = vector::zero;
    glm::vec3 rotation = vector::zero;
    glm::vec3 scale = vector::zero;

    glm::mat4 GetModel();
};  