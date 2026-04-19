#include "Camera.h"

#include <iostream>

Camera::Camera(GameObject* gameObject, float fov, float far, float near) : ComponentSystem::Component(gameObject)
{
    _fov = fov;
    _far = far;
    _near = near;
}

glm::mat4 Camera::GetView()
{
    return glm::lookAt(transform->position, transform->position + transform->rotation, vector::up);
}

glm::mat4 Camera::GetProjection()
{
    return glm::perspective(glm::radians(_fov), (float)Core::getWindowedWidth() / (float)Core::getWindowedHeight(), _near, _far);
}

void Camera::Update()
{

}