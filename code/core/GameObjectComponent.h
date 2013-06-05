#ifndef __GAME_OBJECT_COMPONENT__
#define __GAME_OBJECT_COMPONENT__

#include "BaseObject.h"

// Forward Declarations
class GameObject;


class GameObjectComponent : BaseObject
{
public:

	GameObject *mpGameObject;

	GameObjectComponent( GameObject *pGameObject );

	// Events
	virtual void OnAwake();
	virtual void OnStart();

	virtual void OnUpdate();

	virtual void OnEnable();
	virtual void OnDisable();

	virtual void OnPreRender();
	virtual void OnPostRender();

	virtual void OnRenderObject();
	
	virtual ~GameObjectComponent();
};

#endif