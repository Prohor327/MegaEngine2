#include <Game/Transform.h>

glm::mat4 Transform::GetModel()
{
    glm::mat4 model = glm::mat4(1.0f);

    glm::vec3 rotRad = glm::radians(rotation);

    model = glm::translate(model, position);

    model = glm::rotate(model, rotRad.z, glm::vec3(0, 0, 1));
    model = glm::rotate(model, rotRad.y, glm::vec3(0, 1, 0));  
    model = glm::rotate(model, rotRad.x, glm::vec3(1, 0, 0));  

    model = glm::scale(model, scale);

    return model;
}