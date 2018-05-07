#ifndef __TRANSFORM__
#define __TRANSFORM__
#include "BaseObject.h"
#include "math/Matrix4x4.h"
#include "math/Vector4.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"
#include <vector>
using namespace std;

// Forward Declarations
class GameObject;

class Transform : BaseObject
{
public:

	GameObject *mpGameObject;
	Matrix4x4 mMatWorld;

	Matrix4x4 matScale;
	Matrix4x4 matRotation;
	Matrix4x4 matPosition;

	Vector3 Scale;
	Quaternion Rotation;
	Vector3 Position;
	

	std::vector<Transform*> mChildren;

	Transform( GameObject *pGameObject );
	virtual ~Transform();

	void SetParent(Transform &parent);

	void Update();

	void SetPosition(Vector3 &vecPos);
	void SetLocalPosition(Vector3 &vecPos);

	Vector3 GetLookVector();

	Transform* GetParent();
	void SetParent(Transform *parent);

	void BuildTranslationMatrix();

private:
	Transform *mpParent;
};

#endif