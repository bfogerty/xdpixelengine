#ifndef __GAME_OBJECT_COMPONENT__
#define __GAME_OBJECT_COMPONENT__

#include "BaseObject.h"
#include <map>

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

	typedef GameObjectComponent* (*ComponentClassPointer)(GameObject *, std::map<std::string, std::string>);
	static ComponentClassPointer GetClass( std::string className );

protected:
	static std::map<std::string, ComponentClassPointer> mapComponents;
};

#endif