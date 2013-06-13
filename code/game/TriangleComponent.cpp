#include "TriangleComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "./resource/image_loaders/ImageLoader.h"

//-----------------------------------------------------------------------------------
void TriangleComponent::OnAwake()
{
	this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/mushroom.png");

	Mesh *mesh = mpGameObject->mMesh;

	mesh->verticies.push_back(new Vector3(-1,0,10));
	mesh->verticies.push_back(new Vector3(0,1, 10));
	mesh->verticies.push_back(new Vector3(1,0, 10));

	mesh->colors.push_back(new Color(255,0,0));
	mesh->colors.push_back(new Color(0,255,0));
	mesh->colors.push_back(new Color(0,0,255));

	mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));

	mesh->triangles.push_back(0);
	mesh->triangles.push_back(1);
	mesh->triangles.push_back(2);

	mesh->Build();
}

//-----------------------------------------------------------------------------------
void TriangleComponent::OnUpdate()
{

}