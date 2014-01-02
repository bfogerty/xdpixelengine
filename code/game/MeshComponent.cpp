#include "MeshComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "../core/input/Input.h"

#include "./resource/image_loaders/ImageLoader.h"
#include "./resource/model_loaders/ObjLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"
#include "../renderer/Material.h"

//-----------------------------------------------------------------------------------
void MeshComponent::OnAwake()
{
	Mesh *mesh = mpGameObject->mMesh;

	this->mpGameObject->pTexture = ImageLoader::Load(this->texturePath.c_str());
	Mesh *pMeshTest = ObjLoader::Load(this->modelPath.c_str());

	mesh->Clone(pMeshTest);
}


//-----------------------------------------------------------------------------------
void MeshComponent::OnUpdate()
{

}