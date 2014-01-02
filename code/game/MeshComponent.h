#ifndef __MESH_COMPONENT__
#define __MESH_COMPONENT__
#include "GameObjectComponent.h"

#include "../core/math/Matrix4x4.h"
#include <map>

class MeshComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string model = mapParams["model"];
		std::string texture = mapParams["texture"];

		return (GameObjectComponent*)new MeshComponent(pGameObject, model, texture);
	}

	MeshComponent( GameObject *pGameObject, std::string modelPath, std::string texturePath ) : GameObjectComponent(pGameObject)
	{
		this->modelPath = modelPath;
		this->texturePath = texturePath;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	std::string modelPath;
	std::string texturePath;
};

#endif