#ifndef __MATERIAL_COMPONENT__
#define __MATERIAL_COMPONENT__
#include "core/GameObjectComponent.h"
#include "core/math/Matrix4x4.h"
#include <map>

class MaterialComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string materialFilePath = mapParams["file"];

		return (GameObjectComponent*)new MaterialComponent(pGameObject, materialFilePath);
	}

	MaterialComponent( GameObject *pGameObject, std::string materialFilePath ) : GameObjectComponent(pGameObject)
	{
		this->materialFilePath = materialFilePath;
	}

	virtual void OnAwake();

protected:

	std::string materialFilePath;
};

#endif