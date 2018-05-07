#include "Transform.h"

//-----------------------------------------------------------------------------------
Transform::Transform( GameObject *pGameObject ) 
: mpGameObject(pGameObject)
{
	mChildren.reserve(5);

	mpParent = 0;
	
	Scale = Vector3::One();
	Rotation = Quaternion::AxisAngle(Vector3::Up(), 1.0f);
	Position = Vector3::Zero();
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
	Matrix4x4 mat = Quaternion::ToMatrix(Rotation);
	mat.Transpose();
	Vector4 v4 = mat.GetRow(2);
	Vector3 look( v4.x(), v4.y(), v4.z() );
	look.Normalize();

	return look;
}

//-----------------------------------------------------------------------------------
void Transform::SetPosition(Vector3 &vecPos)
{
	mMatWorld.Translate(vecPos);
}

//-----------------------------------------------------------------------------------
void Transform::SetLocalPosition(Vector3 &vecPos)
{
	
}

//-----------------------------------------------------------------------------------
void Transform::BuildTranslationMatrix()
{
	matPosition.SetIdentity();
	matPosition.Translate(Position);
}

//-----------------------------------------------------------------------------------
void Transform::Update()
{
	matScale.SetIdentity();
	matScale.Set(0,0, Scale.x());
	matScale.Set(1,1, Scale.y());
	matScale.Set(2,2, Scale.z());

	matRotation.SetIdentity();
	matRotation = Quaternion::ToMatrix(Rotation);

	BuildTranslationMatrix();

	mMatWorld = matScale * matRotation * matPosition;
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