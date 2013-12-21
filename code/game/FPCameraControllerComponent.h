#ifndef __FP_CAMERA_CONTROLLER_COMPONENT__
#define __FP_CAMERA_CONTROLLER_COMPONENT__
#include "GameObjectComponent.h"

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

	float Theta;
};

#endif