#ifndef __FULL_SCREEN_QUAD_COMPONENT__
#define __FULL_SCREEN_QUAD_COMPONENT__
#include "core/GameObjectComponent.h"

class FullScreenQuadComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		FullScreenQuadComponent *component = new FullScreenQuadComponent(pGameObject);

		return (GameObjectComponent*)component;
	}

	FullScreenQuadComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{

	}

	virtual void OnAwake();

protected:

};

#endif