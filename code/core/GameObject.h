#ifndef __GAME_OBJECT__
#define __GAME_OBJECT__

#include "BaseObject.h"
#include "GameObjectComponent.h"
#include <string>
#include <vector>
#include "./mesh/Mesh.h"
#include "./resource/texture2d/Texture2D.h"
#include "Material.h"

using namespace std;

// Forward Declarations
class Transform;

class GameObject : BaseObject
{
public:

	enum EPrimitiveType
	{
		Plane = 0,
		Cube,
		Sphere,
		Cylinder,
		Torus,
		Pyramid,
		FullScreenQuad,
	};

	string mName;
	std::vector<int> mComponents1;
	std::vector<GameObjectComponent*> mComponents;
	Transform *mpTransform;
	Mesh *mMesh;
	Texture2D *pTexture;
	Material *pMaterial;
	unsigned int Layer;

	GameObject(string name);
	virtual ~GameObject();

	void AddComponent( GameObjectComponent *component );
	void RemoveComponent( GameObjectComponent *component );

	void OnUpdate();

	unsigned int GetLayer() { return Layer; }
	void SetLayer( unsigned int layer ) { this->Layer = layer; }

	static GameObject* CreatePrimitive( EPrimitiveType type );
};

#endif