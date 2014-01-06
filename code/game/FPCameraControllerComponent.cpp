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
	Theta = 1.00f;
}

//-----------------------------------------------------------------------------------
void FPCameraControllerComponent::OnUpdate()
{
	float dt = Time::GetInstance()->GetSmoothDeltaTime();

	float fCurX = mpGameObject->mpTransform->Position.x();
	float fCurY = mpGameObject->mpTransform->Position.y();
	float fCurZ = mpGameObject->mpTransform->Position.z();

	float fSpeed = 1.0f;
	if( Input::Inst()->GeyKey(KeyCode::LeftShift) ||
		Input::Inst()->GeyKey(KeyCode::RightShift) )
	{
		fSpeed = 5.0f;
	}

	if( Input::Inst()->GeyKey(KeyCode::UpArrow) ||
		Input::Inst()->GeyKey(KeyCode::W) )
	{
		 fCurZ -= (fSpeed * dt);
	}

	if( Input::Inst()->GeyKey(KeyCode::DownArrow) ||
		Input::Inst()->GeyKey(KeyCode::S))
	{
		fCurZ += (fSpeed * dt);
	}

	if( Input::Inst()->GeyKey(KeyCode::LeftArrow) ||
		Input::Inst()->GeyKey(KeyCode::A))
	{
		fCurX -= (fSpeed * dt);
		//Theta -= (fSpeed * Time::GetInstance()->GetDeltaTime());
	}

	if( Input::Inst()->GeyKey(KeyCode::RightArrow) ||
		Input::Inst()->GeyKey(KeyCode::D))
	{
		fCurX += (fSpeed * dt);
		//Theta += (fSpeed * Time::GetInstance()->GetDeltaTime());
	}

	//Theta += 100.0f * Time::GetInstance()->GetDeltaTime();

	if( Theta > 360.0f )
	{
		Theta = 1.0f;
	}
	else if( Theta < 1.0f )
	{
		Theta = 360.0f;
	}
	
	Quaternion q = Quaternion::AxisAngle(Vector3::Up(), Theta);
	Vector3 look = q * Vector3::Forward();
	look.Normalize();


	mpGameObject->mpTransform->Position = Vector3(fCurX, fCurY, fCurZ);
	mpGameObject->mpTransform->Rotation = Quaternion::AxisAngle(Vector3::Up(), Theta);
}