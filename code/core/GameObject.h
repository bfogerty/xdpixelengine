#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "BaseObject.h"
#include "GameObjectComponent.h"
#include <string>
#include <vector>
#include "./mesh/Mesh.h"
#include "./resource/texture2d/Texture2D.h"
using namespace std;

// Forward Declarations
class Transform;

class GameObject : BaseObject
{
public:
	string mName;
	std::vector<int> mComponents1;
	std::vector<GameObjectComponent*> mComponents;
	Transform *mpTransform;
	Mesh *mMesh;
	Texture2D *pTexture;

	GameObject(string name);
	virtual ~GameObject();

	void AddComponent( GameObjectComponent *component );
	void RemoveComponent( GameObjectComponent *component );

	void OnUpdate();
};

#endif