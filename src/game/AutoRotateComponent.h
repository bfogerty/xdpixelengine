#ifndef __AUTO_ROTATE_COMPONENT__
#define __AUTO_ROTATE_COMPONENT__
#include "core/GameObjectComponent.h"
#include "core/math/Vector3.h"

class AutoRotateComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string axis = mapParams["axis"];
		std::string speed = mapParams["speed"];

		float x,y,z;
		sscanf(axis.c_str(), "%f,%f,%f", &x, &y, &z);
		Vector3 vecAxis(x,y,z);

		float s;
		sscanf(speed.c_str(), "%f", &s);


		return (GameObjectComponent*)new AutoRotateComponent(pGameObject, vecAxis, s);
	}

	AutoRotateComponent( GameObject *pGameObject, Vector3 axis, float speed ) : GameObjectComponent(pGameObject)
	{
		this->vecAxis = axis;
		this->speed = speed;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	Vector3 vecAxis;
	float speed;

	float mft;
};

#endif