#include "game/TriangleComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/resource/image_loaders/ImageLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void TriangleComponent::OnAwake()
{
	this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/mushroom.png");

	Mesh *mesh = mpGameObject->mMesh;

	mesh->verticies.push_back(Vector3(-1,0,10));
	mesh->verticies.push_back(Vector3(0,1, 10));
	mesh->verticies.push_back(Vector3(1,0, 10));

	mesh->colors.push_back(new Color(Color::RED));
	mesh->colors.push_back(new Color(Color::RED));
	mesh->colors.push_back(new Color(Color::RED));

	mesh->uvs.push_back(new Vector3(0.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 0.0f, 0.0f));
	mesh->uvs.push_back(new Vector3(1.0f, 1.0f, 0.0f));

	mesh->triangles.push_back( new Face(0,0,0) );
	mesh->triangles.push_back( new Face(0,0,0) );
	mesh->triangles.push_back( new Face(0,0,0) );

	mesh->Build();

	mft = 0.0f;
	mDir = (char)1;

	//mpGameObject->mpTransform->Scale = Vector3::One();
	//mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(Vector3::Up(), 1.0f);
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
		mpGameObject->mpTransform->position = Vector3::Lerp(Vector3(0,-3,0), Vector3(0,3,0), mft);
	}
	else
	{
		mpGameObject->mpTransform->position = Vector3::Lerp( Vector3(0,3,0), Vector3(0,-3,0), mft);
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