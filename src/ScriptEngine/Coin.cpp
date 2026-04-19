#include "Coin.h"

void Scripts::Coin::OnTriggerEnter()
{
	Engine::getActiveScenePtr()->destroyGameObject(gameObject);
}