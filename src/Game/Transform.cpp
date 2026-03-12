#include <Game/Transform.h>

glm::mat4 Transform::GetModel()
{
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, scale);

    return model;
}