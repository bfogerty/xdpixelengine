#ifndef __PLANE_SHADOW_COMPONENT__
#define __PLANE_SHADOW_COMPONENT__
#include "core/GameObject.h"
#include "core/GameObjectComponent.h"
#include "core/math/Matrix4x4.h"
#include <map>

class PlaneShadowComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string gameobjectName = mapParams["gameobject"];
		std::string model = mapParams["model"];
		std::string shader = mapParams["shader"];

		return (GameObjectComponent*)new PlaneShadowComponent(pGameObject, gameobjectName, model, shader);
	}

	PlaneShadowComponent( GameObject *pGameObject, std::string gameObjectName, std::string modelPath, std::string shaderPath ) : GameObjectComponent(pGameObject)
	{
		this->shadowGameObject = 0;
		this->modelPath = modelPath;
		this->shaderPath = shaderPath;

		gameObjectReference = GameObject::Find(gameObjectName);
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	std::string modelPath;
	std::string shaderPath;
	GameObject *shadowGameObject;
	GameObject *gameObjectReference;
};

#endif