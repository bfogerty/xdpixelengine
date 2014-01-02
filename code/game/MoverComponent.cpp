#include "MoverComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "./resource/image_loaders/ImageLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void MoverComponent::OnAwake()
{
	mft = 0.0f;
	mDir = (char)1;
	firstTime = true;
}

//-----------------------------------------------------------------------------------
void MoverComponent::OnUpdate()
{
	if( firstTime )
	{
		startPosition = this->mpGameObject->mpTransform->Position;
		endPosition = startPosition + (vecDir * magnitude);
		firstTime = false;

		return;
	}

	if( mft >= 1.0f )
	{
		mft = 1.0f;
	}

	if( mDir == 1 )
	{
		mpGameObject->mpTransform->Position = Vector3::Lerp(startPosition, endPosition, mft);
	}
	else
	{
		mpGameObject->mpTransform->Position = Vector3::Lerp( endPosition, startPosition, mft);
	}

	if( mft == 1.0f )
	{
		mft = 0.0f;
		mDir ^= 1;
	}
	else
	{
		mft += Time::GetInstance()->GetSmoothDeltaTime() * speed;// GetDeltaTime();
	}
	
}