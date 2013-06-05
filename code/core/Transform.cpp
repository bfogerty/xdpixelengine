#include "Transform.h"

Transform::Transform( GameObject *pGameObject ) 
: mpGameObject(pGameObject)
{
	mChildren.reserve(5);
}

Transform::~Transform()
{
	for(unsigned int i=0; i< mChildren.size(); ++i)
	{
		delete mChildren[i];
		mChildren[i] = NULL;
	}

	mChildren.clear();
}