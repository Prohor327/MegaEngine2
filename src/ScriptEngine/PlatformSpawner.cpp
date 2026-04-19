#include "PlatformSpawner.h"

#include <ScriptEngine/Road.h>

void Scripts::PlatformSpawner::RegisterProperties()
{
	Register_platform();
	Register_length();
	Register_player();
}

void Scripts::PlatformSpawner::Start()
{
	_prefabs.emplace_back(Engine::getActiveScenePtr()->AddPrefabRuntime(platform));
}

void Scripts::PlatformSpawner::Update()
{
	if (player->position.z > _prefabs.back().gameObjects[0]->transform.position.z - 72)
	{
		_nextSpawnPoint.z += 6;
		_prefabs.emplace_back(Engine::getActiveScenePtr()->AddPrefabRuntime(platform, _nextSpawnPoint));
	}

	if (player->position.z > _prefabs[0].gameObjects[0]->transform.position.z + 6)
	{
		//_prefabs[0].gameObjects[0]->GetComponent<Road>()->DestroyCoins();
		Engine::getActiveScenePtr()->destroyGameObject(_prefabs[0].gameObjects[0]);
		_prefabs.erase(_prefabs.begin());
	}
}