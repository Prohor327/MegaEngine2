#include "Cow.h"

void Scripts::Cow::RegisterProperties()
{
	Register_speed();
}

void Scripts::Cow::Update()
{
	transform->position += vector::forward * speed * *deltaTime;


    static bool aWasPressed = false;
    static bool dWasPressed = false;

    bool aPressed = glfwGetKey(Core::getWindow(), GLFW_KEY_A) == GLFW_PRESS;
    bool dPressed = glfwGetKey(Core::getWindow(), GLFW_KEY_D) == GLFW_PRESS;

    int currentLane = static_cast<int>(std::round(transform->position.x / 2.0f)) * 2;

    if (aPressed && !aWasPressed)
    {
        currentLane = std::min(currentLane + 2, 2); 
    }

    if (dPressed && !dWasPressed)
    {
        currentLane = std::max(currentLane - 2, -2);  
    }

    transform->position.x = static_cast<float>(currentLane);

    aWasPressed = aPressed;
    dWasPressed = dPressed;


}

void Scripts::Cow::AddCoin()
{
	_coins++;
	std::cout << "Coins: " << _coins << std::endl;
}