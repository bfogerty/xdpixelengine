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
void Transform::SetParent(Transform &parent)
{
	mpParent = &parent;
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