#include "Cow.h"

void Scripts::Cow::RegisterProperties()
{
	Register_speed();
}

void Scripts::Cow::Update()
{
	transform->position += vector::forward * speed * *deltaTime;

	if (glfwGetKey(Core::getWindow(), GLFW_KEY_A) == GLFW_PRESS)
	{
		if (transform->position.x == 0)
		{
			transform->position.x = -2;
		}
		if (transform->position.x == 2)
		{
			transform->position.x = 0;
		}
	}
	if (glfwGetKey(Core::getWindow(), GLFW_KEY_D) == GLFW_PRESS)
	{
		if (transform->position.x == -2)
		{
			transform->position.x = 0;
		}
		if (transform->position.x == 0)
		{
			transform->position.x = 2;
		}
	}


}

void Scripts::Cow::AddCoin()
{

}