#include "CamerasChanger.h"

#include <Core/Core.h>

void Scripts::CamerasChanger::RegisterProperties()
{
	Register_Camera1();
	Register_Camera2();
    Register_Gb1();
    Register_Gb2();
    Register_Gb3();
    Register_Prefab();
}

void Scripts::CamerasChanger::Update() 
{
    std::cout << Camera1->transform->rotation.x << " " <<
        Camera1->transform->rotation.y << " " <<
        Camera1->transform->rotation.z << std::endl;

    if (glfwGetKey(Core::getWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        if (!_isKeyPressed)
        {
            if (Camera1 && Camera2)
            {
                bool cam1Status = Camera1->GetGameObjPtr()->GetActive();

                Camera1->GetGameObjPtr()->SetActive(!cam1Status);
                Camera2->GetGameObjPtr()->SetActive(cam1Status);
                if (!cam1Status)
                {
                    std::cout << "camera 2 active " << Camera2->transform->rotation.x << " "
                        << Camera2->transform->rotation.y << " "
                        << Camera2->transform->rotation.z << " " << std::endl;
                }
                else
                {
                    std::cout << "camera 1 active " << Camera1->transform->rotation.x << " "
                        << Camera1->transform->rotation.y << " "
                        << Camera1->transform->rotation.z << " " << std::endl;
                }
            }
            _isKeyPressed = true;
        }
    }
    else
    {
        _isKeyPressed = false;
    }

    _time += *deltaTime;

    if (_time >= 5.0f && Gb1 != nullptr)
    {
        Engine::getActiveScenePtr()->destroyGameObject(Gb1);
        Engine::getActiveScenePtr()->AddPrefabRuntime(Prefab, vector::right);
        Gb1 = nullptr;
    }
    if (_time >= 10.0f && Gb2 != nullptr)
    {
        Engine::getActiveScenePtr()->destroyGameObject(Gb2);
        Gb2 = nullptr;
    }
    if (_time >= 15.0f && Gb3 != nullptr)
    {
        Engine::getActiveScenePtr()->destroyGameObject(Gb3);
        Gb3 = nullptr;
    }
}