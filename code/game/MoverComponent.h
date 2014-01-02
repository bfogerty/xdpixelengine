#ifndef __MOVER_COMPONENT__
#define __MOVER_COMPONENT__
#include "GameObjectComponent.h"
#include "../core/math/Vector3.h"

class MoverComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string dir = mapParams["direction"];
		std::string magnitude = mapParams["magnitude"];
		std::string speed = mapParams["speed"];

		float x,y,z;
		sscanf(dir.c_str(), "%f,%f,%f", &x, &y, &z);
		Vector3 vecDir(x,y,z);

		float m;
		sscanf(magnitude.c_str(), "%f", &m);

		float s;
		sscanf(speed.c_str(), "%f", &s);


		return (GameObjectComponent*)new MoverComponent(pGameObject, vecDir, m, s);
	}

	MoverComponent( GameObject *pGameObject, Vector3 dir, float magnitude, float speed ) : GameObjectComponent(pGameObject)
	{
		this->vecDir = dir;
		this->magnitude = magnitude;
		this->speed = speed;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	Vector3 vecDir;
	float magnitude;
	float speed;

	float mft;
	char mDir;

	// Hack until we get a OnStart method hooked up.
	bool firstTime;

	Vector3 startPosition;
	Vector3 endPosition;

};

#endif