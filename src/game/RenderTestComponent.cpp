#include "game/RenderTestComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/resource/image_loaders/ImageLoader.h"

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

	mpGameObject->mpTransform->Scale = Vector3(1,1,1);

	firstTime = true;
}

//-----------------------------------------------------------------------------------
void RenderTestComponent::OnUpdate()
{

	if( firstTime == true )
	{
		startPosition = this->mpGameObject->mpTransform->Position;
		endPosition = startPosition + (Vector3::Right() * 20.0f);

		firstTime = false;

		return;
	}

	if( mT >= 1.0f )
	{
		mT = 1.0f;
	}

	float fAngle = (1.0f - mT)*0.0f + (mT * 359.0f);
	mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(-Vector3::Forward(), fAngle);

	Vector3 pos = startPosition * (1.0f - mT) + (endPosition * mT);
	mpGameObject->mpTransform->Position = pos;


	if( mT >= 1.0f )
	{
		mT = 0.0f;
	}

	mT += Time::GetInstance()->GetDeltaTime() / 4.0f;
}