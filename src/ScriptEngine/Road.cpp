#include "Road.h"

void Scripts::Road::RegisterProperties()
{
	Register_coin();
}

void Scripts::Road::Start()
{
    SpawnCoin(transform->position);
}

void Scripts::Road::SpawnCoin(glm::vec3 offset)
{
    const int width = 3;  
    const int length = 5; 


    int coinCount = 3 + rand() % 3;

    for (int i = 0; i < coinCount; i++)
    {
        int x = rand() % width;
        int z = rand() % length;
        if (x == 0)
        {
            x = 2;
        }
        else if (x == 1)
        {
            x = 0;
        }
        else if (x == 2)
        {
            x = -2;
        }

        std::cout << i << " x " << x << " y " << z << std::endl;

        glm::vec3 randomOffset(x, 1.0f, z);

        _coins.emplace_back(Engine::getActiveScenePtr()->AddPrefabRuntime(coin, offset + randomOffset).gameObjects[0]->GetComponent<Scripts::Coin>());
        if (_coins.back()->GetGameObjPtr()->GetComponent<Road>())
        {
            std::exit(1);
        }
    }
}

void Scripts::Road::DestroyCoins()
{
	for (auto& coin : _coins)
	{
		if (Engine::getActiveScenePtr()->ContainsObject(coin->GetGameObjPtr()))
		{
            if (coin->GetGameObjPtr()->GetComponent<Road>())
            {
                std::exit(1);
            }
			Engine::getActiveScenePtr()->destroyGameObject(coin->GetGameObjPtr());
		}
	}
}