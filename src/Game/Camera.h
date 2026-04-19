#pragma once

#include <Tools/Vector.h>
#include <glm/gtc/matrix_transform.hpp>
#include <Core/Core.h>
#include <Game/Transform.h>
#include <ComponentSystem/Component.h>

class Camera : public ComponentSystem::Component
{
public:
    Camera(GameObject* gameObject, float fov, float far, float near);
    glm::mat4 GetView();
    glm::mat4 GetProjection();
    void Update() override;

private:
    float _fov = 90;
    float _far = 10;
    float _near = 0;
};