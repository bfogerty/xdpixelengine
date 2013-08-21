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


//-----------------------------------------------------------------------------------
void ObjLoaderTestComponent::OnAwake()
{
	Mesh *mesh = mpGameObject->mMesh;

	Mesh *pMeshTest = ObjLoader::Load("./assets/models/man.obj");
	mesh->Clone(pMeshTest);

	mft = 0.0f;

	fX = 0.0f;
	fY = 0.0f;
	fZ = 1.0f;

	mpSphere = GameObject::CreatePrimitive(GameObject::Plane);
	mpSphere->mpTransform->SetParent(*mpGameObject->mpTransform);
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

	this->mpSphere->mpTransform->Scale = Vector3(0.5f,0.5f,0.5f);
	this->mpSphere->mpTransform->Rotation = Quaternion::AxisAngle(Vector3::Up(), fDegrees);
	this->mpSphere->mpTransform->Position = Vector3(fX,fY,fZ);

	mft += Time::GetInstance()->GetDeltaTime() / 5;

	/*
	if( Input::Inst()->GeyKey(KeyCode::LeftArrow) ||
		Input::Inst()->GeyKey(KeyCode::A) )
	{
		fX -= (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::RightArrow) ||
		Input::Inst()->GeyKey(KeyCode::D))
	{
		fX += (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::UpArrow) )
	{
		fY += (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::DownArrow) )
	{
		fY -= (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::W) )
	{
		fZ += (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::S) )
	{
		fZ -= (1.f * Time::GetInstance()->GetDeltaTime());
	}
	*/
}