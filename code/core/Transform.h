#ifndef __TRANSFORM__
#define __TRANSFORM__
#include "BaseObject.h"
#include <vector>
using namespace std;

// Forward Declarations
class GameObject;

class Transform : BaseObject
{
public:

	GameObject *mpGameObject;
	std::vector<Transform*> mChildren;

	Transform( GameObject *pGameObject );
	virtual ~Transform();
};

#endif