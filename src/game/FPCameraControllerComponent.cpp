#include "FPCameraControllerComponent.h"

#include "../core/config/EngineConfig.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "../core/input/Input.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"

#include "windows.h"

//-----------------------------------------------------------------------------------
void FPCameraControllerComponent::OnAwake()
{
	yaw = 0.001f;
	pitch = 0.001f;
}

//-----------------------------------------------------------------------------------
void FPCameraControllerComponent::OnUpdate()
{
	Vector3 camPos = this->mpGameObject->mpTransform->position;
	//Vector3 camLook = this->mpGameObject->mpTransform->GetLookVector();

	Vector3 camLook =  this->mpGameObject->mpTransform->rotation * Vector3(0,0.00f,1.0f);
	Vector3 camLeft =  this->mpGameObject->mpTransform->rotation * Vector3(1.0f,0.00f,0.0f);

	float dt = Time::GetInstance()->GetDeltaTime();

	float fSpeed = 1.0f;
	if( Input::Inst()->GeyKey(KeyCode::LeftShift) ||
		Input::Inst()->GeyKey(KeyCode::RightShift) )
	{
		fSpeed = 5.0f;
	}

	if( Input::Inst()->GeyKey(KeyCode::UpArrow) ||
		Input::Inst()->GeyKey(KeyCode::W) )
	{
		camPos = camPos + (camLook *(fSpeed * dt));
	}

	if( Input::Inst()->GeyKey(KeyCode::DownArrow) ||
		Input::Inst()->GeyKey(KeyCode::S))
	{
		camPos = camPos - (camLook *(fSpeed * dt));
	}

	if( Input::Inst()->GeyKey(KeyCode::LeftArrow) ||
		Input::Inst()->GeyKey(KeyCode::A))
	{
		camPos = camPos - (camLeft *(fSpeed * dt));
	}

	if( Input::Inst()->GeyKey(KeyCode::RightArrow) ||
		Input::Inst()->GeyKey(KeyCode::D))
	{
		camPos = camPos + (camLeft *(fSpeed * dt));
	}

	if( Input::Inst()->GetMouseButton( MouseKeyCode::Right ) )
	{
		Input::Inst()->ShowMouseCursor( FALSE );

		Vector3 origin;
		origin.x( (EngineConfig::renderConfig.ScreenWidth / 2.00f));
		origin.y( (EngineConfig::renderConfig.ScreenHeight / 2.00f));

		Vector3 windowPos = Input::Inst()->GetWindowPositionInScreenSpace();
		Vector3 realOrigin = windowPos + origin;

		Vector3 currentPos = Input::Inst()->GetMousePosition();

		if( justPressed )
		{
			currentPos = realOrigin;
			Input::Inst()->SetMousePosition( realOrigin );
			justPressed = FALSE;
		}

		Vector3 delta = currentPos - realOrigin;
		
		//sprintf( buffer, "cy=%f, oy=%f\n", currentPos.y(), origin.y());
		//OutputDebugString( buffer );

		float dx = delta.x();
		float dy = delta.y();
		if((abs(dx) > 0.01f || abs(dy) > 0.01f ))
		{
			yaw += (dx * 0.10f);
			pitch += (dy * 0.10f);
		}

		Input::Inst()->SetMousePosition( realOrigin );
	}
	else
	{
		Input::Inst()->ShowMouseCursor( TRUE );
		justPressed = TRUE;
	}

	angles.x(pitch);
	angles.y(yaw);
	angles.z(0.00f);

	mpGameObject->mpTransform->position = camPos;
	mpGameObject->mpTransform->rotation = Quaternion::FromEulerAngles(angles);
}