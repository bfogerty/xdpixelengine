#include "RenderTestComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"

//-----------------------------------------------------------------------------------
void RenderTestComponent::OnAwake()
{
	Mesh *mesh = mpGameObject->mMesh;

	// OpenGL Version
	/*
	mesh->verticies.push_back(new Vector3(-1,0,-10));
	mesh->verticies.push_back(new Vector3(0,1,-10));
	mesh->verticies.push_back(new Vector3(1,0,-10));
	*/

	// DirectX Version
	mesh->verticies.push_back(new Vector3(-1,0,10));
	mesh->verticies.push_back(new Vector3(0,1, 10));
	mesh->verticies.push_back(new Vector3(1,0, 10));

	mesh->colors.push_back(new Color(Color::GREEN));
	mesh->colors.push_back(new Color(Color::BLUE));
	mesh->colors.push_back(new Color(Color::RED));

	mesh->triangles.push_back(0);
	mesh->triangles.push_back(1);
	mesh->triangles.push_back(2);

	mesh->Build();
}