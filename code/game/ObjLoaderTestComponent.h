#ifndef __OBJ_LOADER_TEST_COMPONENT__
#define __OBJ_LOADER_TEST_COMPONENT__
#include "GameObjectComponent.h"

#include "../core/math/Matrix4x4.h"

class ObjLoaderTestComponent : public GameObjectComponent
{
public:

	ObjLoaderTestComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{

	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	float mft;
	char mDir;

	float fX;
	float fY;
	float fZ;

	GameObject *mpSphere;
	GameObject *mpCube;

};

#endif