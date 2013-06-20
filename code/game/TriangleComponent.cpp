#include "TriangleComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "./resource/image_loaders/ImageLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void TriangleComponent::OnAwake()
{
	this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/mushroom.png");

	Mesh *mesh = mpGameObject->mMesh;

	mesh->verticies.push_back(new Vector3(-1,0,10));
	mesh->verticies.push_back(new Vector3(0,1, 10));
	mesh->verticies.push_back(new Vector3(1,0, 10));

	mesh->colors.push_back(new Color(Color::RED));
	mesh->colors.push_back(new Color(Color::RED));
	mesh->colors.push_back(new Color(Color::RED));

	mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));

	mesh->triangles.push_back(0);
	mesh->triangles.push_back(1);
	mesh->triangles.push_back(2);

	mesh->Build();

	//mpGameObject->mpTransform->SetPosition( Vector3(0,-2,0) );
	mft = 0.0f;
	mDir = (char)1;

	Vector3 vP(1.0f,0.0f,0.0f);
	Vector3 vAxis(0.0f,1.0f,0.0f);
	Quaternion qRot = Quaternion::AxisAngle(vAxis, -90.0f);

	vP = qRot * vP;

}

//-----------------------------------------------------------------------------------
void TriangleComponent::OnUpdate()
{
	if( mft >= 1.0f )
	{
		mft = 1.0f;
	}


	if( mDir == 1 )
	{
		mpGameObject->mpTransform->SetPosition( Vector3::Lerp(Vector3(0,-3,0), Vector3(0,3,0), mft) );
	}
	else
	{
		mpGameObject->mpTransform->SetPosition( Vector3::Lerp( Vector3(0,3,0), Vector3(0,-3,0), mft) );
	}

	if( mft == 1.0f )
	{
		mft = 0.0f;
		mDir ^= 1;
	}
	else
	{
		mft += Time::GetInstance()->GetDeltaTime();
	}
	
}