#ifndef __MOVER_COMPONENT__
#define __MOVER_COMPONENT__
#include "GameObjectComponent.h"
#include "../core/math/Vector3.h"

class MoverComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		return (GameObjectComponent*)new MoverComponent(pGameObject);
	}

	MoverComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{

	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	float mft;
	char mDir;

	// Hack until we get a OnStart method hooked up.
	bool firstTime;

	Vector3 startPosition;
	Vector3 endPosition;

};

#endif