#ifndef __FP_CAMERA_CONTROLLER_COMPONENT__
#define __FP_CAMERA_CONTROLLER_COMPONENT__
#include "core/GameObjectComponent.h"
#include "core/math/Vector3.h"

class FPCameraControllerComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		return (GameObjectComponent*)new FPCameraControllerComponent(pGameObject);
	}

	FPCameraControllerComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
	{

	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	float yaw;
	float pitch;
	Vector3 angles;

	char buffer[300];
};

#endif