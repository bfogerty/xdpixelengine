#ifndef __TRANSFORM__
#define __TRANSFORM__
#include "BaseObject.h"
#include "math/Matrix4x4.h"
#include "math/Vector4.h"
#include "math/Vector3.h"
#include <vector>
using namespace std;

// Forward Declarations
class GameObject;

class Transform : BaseObject
{
public:

	GameObject *mpGameObject;
	Matrix4x4 mMatWorld;
	Transform *mpParent;

	std::vector<Transform*> mChildren;

	Transform( GameObject *pGameObject );
	virtual ~Transform();

	void SetParent(Transform &parent);

	void SetPosition(Vector3 &vecPos);
	void SetLocalPosition(Vector3 &vecPos);
};

#endif