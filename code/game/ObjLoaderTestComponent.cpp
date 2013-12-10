#include "ObjLoaderTestComponent.h"
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
void ObjLoaderTestComponent::OnAwake()
{

	this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/blade_blue.png");

	Mesh *mesh = mpGameObject->mMesh;

	Mesh *pMeshTest = ObjLoader::Load("./assets/models/tekka.obj");
	//Mesh *pMeshTest = GameObject::CreatePrimitive( GameObject::EPrimitiveType::Torus )->mMesh;
	mesh->Clone(pMeshTest);

	mft = 0.0f;

	fX = 0.0f;
	fY = 0.15f;
	fZ = 1.0f;
}


//-----------------------------------------------------------------------------------
void ObjLoaderTestComponent::OnUpdate()
{
	if( mft >= 1.0f )
	{
		mft = 0.0001f;
	}

	float fDegrees = (mft*360.0f);

	this->mpGameObject->mpTransform->Scale = Vector3(0.05f,0.05f,0.05f);
	this->mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(Vector3::Up(), fDegrees);
	this->mpGameObject->mpTransform->Position = Vector3(fX,fY,fZ);

	mft += Time::GetInstance()->GetDeltaTime() / 5;
}