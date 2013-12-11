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

	Mesh *mesh = mpGameObject->mMesh;

	//this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/blade_blue.png");
	//Mesh *pMeshTest = ObjLoader::Load("./assets/models/tekka_op.obj");

	//this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/Robot_Color.png");
	//Mesh *pMeshTest = ObjLoader::Load("./assets/models/Robot2.obj");

	this->mpGameObject->pTexture = ImageLoader::Load(this->texturePath);
	Mesh *pMeshTest = ObjLoader::Load(this->modelPath);

	mesh->Clone(pMeshTest);

	mft = 0.0f;
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

	mft += Time::GetInstance()->GetDeltaTime() / 5;
}