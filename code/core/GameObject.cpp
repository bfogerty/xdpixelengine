#include "GameObject.h"
#include "Transform.h"

GameObject::GameObject( string Name )
{
	mName = Name;
	mComponents.reserve(10);
	mpTransform = new Transform( this );

	mMesh = new Mesh();
}

GameObject::~GameObject()
{
	for( unsigned int i=0; i < mComponents.size(); ++i )
	{
		delete mComponents[i];
		mComponents[i] = NULL;
	}

	mComponents.clear();

	delete mpTransform;
	mpTransform = NULL;

	delete mMesh;
	mMesh = NULL;
}

void GameObject::AddComponent( GameObjectComponent *component )
{
	for( unsigned int i=0; i< mComponents.size(); ++i )
	{
		if( mComponents[i] == component )
		{
			return;
		}
	}

	mComponents.push_back( component );
	component->OnAwake();
	component->OnStart();
}

void GameObject::RemoveComponent( GameObjectComponent *component )
{
	int iIndex = -1;
	for( unsigned int i=0; i< mComponents.size(); ++i )
	{
		if( mComponents[i] == component )
		{
			iIndex = i;
			break;
		}
	}

	if( iIndex != -1 )
	{
		mComponents.erase( mComponents.begin() + iIndex );
	}
}

void GameObject::OnUpdate()
{
	for( unsigned int i=0; i < mComponents.size(); ++i )
	{
		mComponents[i]->OnUpdate();
	}
}