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

	GameObject *gameObject;
	Matrix4x4 worldMatrix;

	Matrix4x4 scaleMatrix;
	Matrix4x4 rotationMatrix;
	Matrix4x4 translationMatrix;

	Vector3 scale;
	Quaternion rotation;
	Vector3 position;
	

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