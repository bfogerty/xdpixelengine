#include "game/MeshComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/input/Input.h"

#include "core/resource/image_loaders/ImageLoader.h"
#include "core/resource/model_loaders/ObjLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"
#include "graphics/Material.h"

//-----------------------------------------------------------------------------------
void MeshComponent::OnAwake()
{
	Mesh *mesh = mpGameObject->mMesh;

	Mesh *pMeshTest = ObjLoader::Load(this->modelPath.c_str());

	mesh->Clone(pMeshTest);
}


//-----------------------------------------------------------------------------------
void MeshComponent::OnUpdate()
{

}