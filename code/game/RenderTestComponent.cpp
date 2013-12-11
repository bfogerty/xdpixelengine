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
	

	for( int i=0; i< 6; ++i )
	{
		mesh->triangles.push_back(new Face(i,i,i,i) );
	}

	mesh->Build();

	id = iID;
	++iID;

	mpGameObject->mpTransform->Scale = Vector3(1,1,1);
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

	Vector3 vecStart(-7.0f, fY, 5.0f);
	Vector3 vecEnd(7.0f, fY, 5.0f);

	if( mT >= 1.0f )
	{
		mT = 1.0f;
	}

	float fAngle = (1.0f - mT)*0.0f + (mT * 359.0f);
	mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(-Vector3::Forward(), fAngle);

	Vector3 pos = vecStart * (1.0f - mT) + (vecEnd * mT);
	mpGameObject->mpTransform->Position = pos;


	if( mT >= 1.0f )
	{
		mT = 0.0f;
	}

	mT += Time::GetInstance()->GetDeltaTime() / 4.0f;
}