#ifndef __RENDER_TEST_COMPONENT__
#define __RENDER_TEST_COMPONENT__
#include "core/GameObjectComponent.h"
#include "core/math/Vector3.h"

class RenderTestComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		RenderTestComponent *component = new RenderTestComponent(pGameObject);

		return (GameObjectComponent*)component;
	}

	RenderTestComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{
		
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:
	float mT;
	int id;

	Vector3 startPosition;
	Vector3 endPosition;

	bool firstTime;
};

#endif