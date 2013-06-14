#ifndef __GAME_MAIN_COMPONENT__
#define __GAME_MAIN_COMPONENT__
#include "GameObjectComponent.h"

class GameMain : public GameObjectComponent
{
public:

	GameMain( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{

	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

};

#endif