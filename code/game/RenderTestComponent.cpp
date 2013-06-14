#include "RenderTestComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "./resource/image_loaders/ImageLoader.h"

int RenderTestComponent::iID = 0;

//-----------------------------------------------------------------------------------
void RenderTestComponent::OnAwake()
{
	this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/mushroom.png");
	mT = 0.0f;

	Mesh *mesh = mpGameObject->mMesh;

	// DirectX Version
	mesh->verticies.push_back(new Vector3(-1,-1,10));
	mesh->verticies.push_back(new Vector3(-1,1, 10));
	mesh->verticies.push_back(new Vector3(1,1, 10));
	mesh->verticies.push_back(new Vector3(-1,-1,10));
	mesh->verticies.push_back(new Vector3(1,1, 10));
	mesh->verticies.push_back(new Vector3(1,-1, 10));

	mesh->colors.push_back(new Color(Color::GREEN));
	mesh->colors.push_back(new Color(Color::BLUE));
	mesh->colors.push_back(new Color(Color::RED));
	mesh->colors.push_back(new Color(Color::GREEN));
	mesh->colors.push_back(new Color(Color::RED));
	mesh->colors.push_back(new Color(Color::BLUE));
	

	mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(0.0f, 1.0f, 0.0f));	
	

	mesh->triangles.push_back(0);
	mesh->triangles.push_back(1);
	mesh->triangles.push_back(2);
	mesh->triangles.push_back(3);
	mesh->triangles.push_back(4);
	mesh->triangles.push_back(5);

	mesh->Build();

	id = iID;
	++iID;
}

//-----------------------------------------------------------------------------------
void RenderTestComponent::OnUpdate()
{
	float fY = 3.0f;
	if( id == 1 )
	{
		fY = -3.0f;
	}
	else if( id == 2 )
	{
		fY = -6.0f;
	}

	Vector3 vecStart(-7.0f, fY, 0.0f);
	Vector3 vecEnd(7.0f, fY, 0.0f);

	if( mT >= 1.0f )
	{
		mT = 1.0f;
	}

	float fAngle = (1.0f - mT)*0.0f + (mT * 359.0f);
	Matrix4x4 matRot;
	matRot.RotationZ(fAngle);

	Vector3 pos = vecStart * (1.0f - mT) + (vecEnd * mT);
	Matrix4x4 matPos;
	matPos.Translate(pos);
	mpGameObject->mpTransform->mMatWorld = matRot * matPos;

	if( mT >= 1.0f )
	{
		mT = 0.0f;
	}

	mT += Time::GetInstance()->GetDeltaTime() / 4.0f;
}