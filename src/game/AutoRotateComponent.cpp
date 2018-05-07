#include "game/AutoRotateComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/resource/image_loaders/ImageLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void AutoRotateComponent::OnAwake()
{
	mft = 0.001f;
	vecAxis.Normalize();
}

//-----------------------------------------------------------------------------------
void AutoRotateComponent::OnUpdate()
{
	if( mft >= 1.0f )
	{
		mft= 0.0001f;
	}

	float theta = (1.0f - mft) * 0.0001f + (mft * 360.00f);

	if( theta > 360.0f )
	{
		theta = 360.001f;
		mft = 1.0f;
	}

	this->mpGameObject->mpTransform->rotation = Quaternion::AxisAngle(vecAxis, theta);

	mft += Time::GetInstance()->GetSmoothDeltaTime() * speed;
	
}