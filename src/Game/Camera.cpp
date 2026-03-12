#include "Camera.h"

Camera::Camera(GameObject* gameObject, float fov, float far, float near) : ComponentSystem::Component(gameObject)
{
    _fov = fov;
    _far = far;
    _near = near;
}

glm::mat4 Camera::GetView()
{
    glm::vec3 direction;
    float pitch = transform->rotation.x;
    float yaw = transform->rotation.y;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    return glm::lookAt(transform->position, transform->position + direction, vector::up);
}

glm::mat4 Camera::GetProjection()
{
    return glm::perspective(glm::radians(_fov), (float)Core::getWindowedWidth() / (float)Core::getWindowedHeight(), _near, _far);
}