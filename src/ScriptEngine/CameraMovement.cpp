#include "CameraMovement.h"

#include <Core/Core.h>

void Scripts::CameraMovement::RegisterProperties()
{
	Register_pitchLimit();
	Register_sens();
	Register_speed();
}

void Scripts::CameraMovement::Update()
{
	transform->position = Engine::getActiveScenePtr()->GetObjectPtrByName("Cow")->transform.position + glm::vec3(-4, 4, -3);

	//double xpos, ypos;
	//glfwGetCursorPos(Core::getWindow(), &xpos, &ypos);

	//_mouseX = static_cast<float>(xpos);
	//_mouseY = static_cast<float>(ypos);

	//float deltaPosX = _mouseX - _lastMouseX;
	//float deltaPosY = _lastMouseY - _mouseY;

	//_lastMouseX = _mouseX;
	//_lastMouseY = _mouseY;

	//_yaw += deltaPosX * sens;
	//_pitch += deltaPosY * sens;

	//_pitch = glm::clamp(_pitch, -pitchLimit, pitchLimit);

	//glm::vec3 front;
	//front.x = cos(glm::radians(_yaw)) * cos(glm::radians(_pitch));
	//front.y = sin(glm::radians(_pitch));
	//front.z = sin(glm::radians(_yaw)) * cos(glm::radians(_pitch));

	//transform->rotation = glm::normalize(front);

	//if (glfwGetKey(Core::getWindow(), GLFW_KEY_W) == GLFW_PRESS)
	//	transform->position += speed * transform->rotation;
	//if (glfwGetKey(Core::getWindow(), GLFW_KEY_S) == GLFW_PRESS)
	//	transform->position -= speed * transform->rotation;
	//if (glfwGetKey(Core::getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	//	transform->position -= glm::normalize(glm::cross(transform->rotation, vector::up)) * speed;
	//if (glfwGetKey(Core::getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	//	transform->position += glm::normalize(glm::cross(transform->rotation, vector::up)) * speed;
}

void Scripts::CameraMovement::OnGameObjectEnable()
{
	_yaw = transform->rotation.y;
	_pitch = transform->rotation.x;
}
