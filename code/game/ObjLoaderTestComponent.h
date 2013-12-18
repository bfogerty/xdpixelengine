#ifndef __OBJ_LOADER_TEST_COMPONENT__
#define __OBJ_LOADER_TEST_COMPONENT__
#include "GameObjectComponent.h"

#include "../core/math/Matrix4x4.h"
#include <map>

class ObjLoaderTestComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string model = mapParams["model"];
		std::string texture = mapParams["texture"];

		return (GameObjectComponent*)new ObjLoaderTestComponent(pGameObject, model, texture);
	}

	ObjLoaderTestComponent( GameObject *pGameObject, std::string modelPath, std::string texturePath ) : GameObjectComponent(pGameObject)
	{
		this->modelPath = modelPath;
		this->texturePath = texturePath;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	std::string modelPath;
	std::string texturePath;

	float mft;
	char mDir;

	float fX;
	float fY;
	float fZ;

	GameObject *mpSphere;
	GameObject *mpCube;

};

#endif