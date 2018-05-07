#include "Transform.h"

//-----------------------------------------------------------------------------------
Transform::Transform( GameObject *pGameObject ) 
: gameObject(pGameObject)
{
	mChildren.reserve(5);

	mpParent = 0;
	
	scale = Vector3::One();
	rotation = Quaternion::AxisAngle(Vector3::Up(), 1.0f);
	position = Vector3::Zero();
}

//-----------------------------------------------------------------------------------
Transform::~Transform()
{
	for(unsigned int i=0; i< mChildren.size(); ++i)
	{
		delete mChildren[i];
		mChildren[i] = NULL;
	}

	mChildren.clear();
}

//-----------------------------------------------------------------------------------
Vector3 Transform::GetLookVector()
{
	Matrix4x4 mat = Quaternion::ToMatrix(rotation);
	mat.Transpose();
	Vector4 v4 = mat.GetRow(2);
	Vector3 look( v4.x(), v4.y(), v4.z() );
	look.Normalize();

	return look;
}

//-----------------------------------------------------------------------------------
void Transform::SetPosition(Vector3 &vecPos)
{
	worldMatrix.Translate(vecPos);
}

//-----------------------------------------------------------------------------------
void Transform::SetLocalPosition(Vector3 &vecPos)
{
	
}

//-----------------------------------------------------------------------------------
void Transform::BuildTranslationMatrix()
{
	translationMatrix.SetIdentity();
	translationMatrix.Translate(position);
}

//-----------------------------------------------------------------------------------
void Transform::Update()
{
	scaleMatrix.SetIdentity();
	scaleMatrix.Set(0,0, scale.x());
	scaleMatrix.Set(1,1, scale.y());
	scaleMatrix.Set(2,2, scale.z());

	rotationMatrix.SetIdentity();
	rotationMatrix = Quaternion::ToMatrix(rotation);

	BuildTranslationMatrix();

	worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;
}

//-----------------------------------------------------------------------------------
Transform* Transform::GetParent()
{
	return mpParent;
}

//-----------------------------------------------------------------------------------
void Transform::SetParent(Transform &parent)
{
	if( mpParent != 0 )
	{
		//mpParent->mChildren.erase(this);
	}

	mpParent = &parent;
	mpParent->mChildren.push_back(this);
}