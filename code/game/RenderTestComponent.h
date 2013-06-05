#ifndef __RENDER_TEST_COMPONENT__
#define __RENDER_TEST_COMPONENT__
#include "GameObjectComponent.h"

class RenderTestComponent : public GameObjectComponent
{
public:

	RenderTestComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{

	}

	virtual void OnAwake();

};

#endif