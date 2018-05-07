#ifndef __MESH_COMPONENT__
#define __MESH_COMPONENT__
#include "core/GameObjectComponent.h"

#include "core/math/Matrix4x4.h"
#include <map>

class MeshComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string model = mapParams["model"];

		return (GameObjectComponent*)new MeshComponent(pGameObject, model);
	}

	MeshComponent( GameObject *pGameObject, std::string modelPath ) : GameObjectComponent(pGameObject)
	{
		this->modelPath = modelPath;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	std::string modelPath;
};

#endif