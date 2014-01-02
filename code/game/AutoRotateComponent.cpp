#include "AutoRotateComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "./resource/image_loaders/ImageLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void AutoRotateComponent::OnAwake()
{
	mft = 0.001f;
	vecAxis.Normalize();
}

//-----------------------------------------------------------------------------------
void AutoRotateComponent::OnUpdate()
{
	float theta = (1.0f - mft) * 0.0001f + (mft * 360.00f);

	if( theta > 360.0f )
	{
		theta = 0.001f;
		mft = 0.001f;
	}

	this->mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(vecAxis, theta);

	mft += Time::GetInstance()->GetSmoothDeltaTime() * speed;
	
}