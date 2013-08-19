#include "Transform.h"

//-----------------------------------------------------------------------------------
Transform::Transform( GameObject *pGameObject ) 
: mpGameObject(pGameObject)
{
	mChildren.reserve(5);

	mpParent = 0;
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
void Transform::SetPosition(Vector3 &vecPos)
{
	mMatWorld.Translate(vecPos);
}

//-----------------------------------------------------------------------------------
void Transform::SetLocalPosition(Vector3 &vecPos)
{
	
}

//-----------------------------------------------------------------------------------
void Transform::Update()
{
	matScale.SetIdentity();
	matScale.UniformScale(Scale.x());
	
	matRotation.SetIdentity();
	matRotation = Quaternion::ToMatrix(Rotation);

	matPosition.SetIdentity();
	matPosition.Translate(Position);


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