#ifndef __OBJ_LOADER_TEST_COMPONENT__
#define __OBJ_LOADER_TEST_COMPONENT__
#include "GameObjectComponent.h"

#include "../core/math/Matrix4x4.h"

class ObjLoaderTestComponent : public GameObjectComponent
{
public:

	ObjLoaderTestComponent( GameObject *pGameObject, char* modelPath, char* texturePath ) : GameObjectComponent(pGameObject)
	{
		this->modelPath = modelPath;
		this->texturePath = texturePath;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	char* modelPath;
	char* texturePath;

	float mft;
	char mDir;

	float fX;
	float fY;
	float fZ;

	GameObject *mpSphere;
	GameObject *mpCube;

};

#endif