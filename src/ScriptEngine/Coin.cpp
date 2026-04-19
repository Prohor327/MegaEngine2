#include "Coin.h"

#include <ScriptEngine/Cow.h>

void Scripts::Coin::OnTriggerEnter(GameObject* gameObject)
{

	Engine::getActiveScenePtr()->destroyGameObject(this->gameObject);

	if (gameObject->GetComponent<Cow>())
	{
		gameObject->GetComponent<Cow>()->AddCoin();
	}
}