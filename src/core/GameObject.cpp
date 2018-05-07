#include "GameObject.h"
#include "Transform.h"
#include "./resource/model_loaders/ObjLoader.h"

vector<GameObject*> GameObject::GameObjectList;

GameObject::GameObject( string Name )
{
	mName = Name;
	mComponents.reserve(10);
	mpTransform = new Transform( this );

	mMesh = new Mesh();
	pTexture = 0;
	pMaterial = 0;
	
	GameObjectList.push_back(this);
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

	// TODO: Remove from GameObjectList
}

GameObject* GameObject::Find(std::string name)
{
	for(vector<GameObject*>::iterator it = GameObjectList.begin(); it != GameObjectList.end(); ++it)
	{
		GameObject *obj = *it;
		if( name == obj->mName )
		{
			return obj;
		}
	}

	return 0;
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
	else if( type == FullScreenQuad )
	{
		pGO = new GameObject("FullScreenQuad");
		Mesh *mesh = new Mesh();
		
		mesh->verticies.push_back( Vector3(-1,-1,1));
		mesh->verticies.push_back( Vector3(-1,1, 1));
		mesh->verticies.push_back( Vector3(1,1, 1));
		mesh->verticies.push_back( Vector3(-1,-1,1));
		mesh->verticies.push_back( Vector3(1,1, 1));
		mesh->verticies.push_back( Vector3(1,-1, 1));

		mesh->colors.push_back(new Color(Color::RED));
		mesh->colors.push_back(new Color(Color::RED));
		mesh->colors.push_back(new Color(Color::RED));
		mesh->colors.push_back(new Color(Color::RED));
		mesh->colors.push_back(new Color(Color::RED));
		mesh->colors.push_back(new Color(Color::RED));

		mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
		mesh->uvs.push_back(new Vector3(1.0f, 0.0f, 0.0f));
		mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));
		mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
		mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));
		mesh->uvs.push_back(new Vector3(0.0f, 1.0f, 0.0f));	

		mesh->normals.push_back(new Vector3(0.0f, 0.0f, 1.0f));
		mesh->normals.push_back(new Vector3(0.0f, 0.0f, 1.0f));
		mesh->normals.push_back(new Vector3(0.0f, 0.0f, 1.0f));
		mesh->normals.push_back(new Vector3(0.0f, 0.0f, 1.0f));
		mesh->normals.push_back(new Vector3(0.0f, 0.0f, 1.0f));
		mesh->normals.push_back(new Vector3(0.0f, 0.0f, 1.0f));

		for( int i=0; i< 6; ++i )
		{
			mesh->triangles.push_back(new Face(i,i,i,i) );
		}

		pGO->mMesh->Clone(mesh);
	}

	return pGO;
}

vector<GameObject*> GameObject::GetGameObjectList()
{
	return GameObjectList;
}