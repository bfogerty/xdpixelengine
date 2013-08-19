#include "GameObject.h"
#include "Transform.h"
#include "./resource/model_loaders/ObjLoader.h"

GameObject::GameObject( string Name )
{
	mName = Name;
	mComponents.reserve(10);
	mpTransform = new Transform( this );

	mMesh = new Mesh();
	pTexture = 0;
	
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
	mpTransform = 0;

	delete mMesh;
	mMesh = 0;

	pTexture = 0;
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

GameObject* GameObject::CreatePrimitive( EPrimitiveType type )
{
	GameObject *pGO = 0;

	if( type == Plane )
	{
		pGO = new GameObject("Plane");
		Mesh *pMeshTest = ObjLoader::Load("./assets/models/primitives/Plane.obj");
		pGO->mMesh->Clone(pMeshTest);
	}
	else if( type == Sphere )
	{
		pGO = new GameObject("Sphere");
		Mesh *pMeshTest = ObjLoader::Load("./assets/models/primitives/Sphere.obj");
		pGO->mMesh->Clone(pMeshTest);
	}
	else if( type == Cube )
	{
		pGO = new GameObject("Cube");
		Mesh *pMeshTest = ObjLoader::Load("./assets/models/primitives/Cube.obj");
		pGO->mMesh->Clone(pMeshTest);
	}
	else if( type == Cylinder )
	{
		pGO = new GameObject("Cylinder");
		Mesh *pMeshTest = ObjLoader::Load("./assets/models/primitives/Cylinder.obj");
		pGO->mMesh->Clone(pMeshTest);
	}
	else if( type == Torus )
	{
		pGO = new GameObject("Torus");
		Mesh *pMeshTest = ObjLoader::Load("./assets/models/primitives/Torus.obj");
		pGO->mMesh->Clone(pMeshTest);
	}
	else if( type == Pyramid )
	{
		pGO = new GameObject("Pyramid");
		Mesh *pMeshTest = ObjLoader::Load("./assets/models/primitives/Pyramid.obj");
		pGO->mMesh->Clone(pMeshTest);
	}

	return pGO;
}