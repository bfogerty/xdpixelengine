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

	std::vector<Transform*> mChildren;

	Transform( GameObject *pGameObject );
	virtual ~Transform();
};

#endif