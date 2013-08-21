#include "FPCameraControllerComponent.h"

#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "../core/input/Input.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void FPCameraControllerComponent::OnAwake()
{
	Theta = 1.0f;
}

//-----------------------------------------------------------------------------------
void FPCameraControllerComponent::OnUpdate()
{
	float fCurX = mpGameObject->mpTransform->Position.x();
	float fCurY = mpGameObject->mpTransform->Position.y();
	float fCurZ = mpGameObject->mpTransform->Position.z();

	if( Input::Inst()->GeyKey(KeyCode::UpArrow) )
	{
		 fCurZ += (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::DownArrow) )
	{
		fCurZ -= (1.f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::LeftArrow) )
	{
		Theta += (45.0f * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::RightArrow) )
	{
		Theta -= (45.0f * Time::GetInstance()->GetDeltaTime());
	}

	/*
	if( Theta > 360.0f )
	{
		Theta = 1.0f;
	}
	else if( Theta < 1.0f )
	{
		Theta = 360.0f;
	}
	*/

	mpGameObject->mpTransform->Position = Vector3(fCurX, fCurY, fCurZ);
	mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(Vector3::Up(), Theta);
}