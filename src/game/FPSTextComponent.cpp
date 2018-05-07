#include "game/FPSTextComponent.h"
#include "game/TextComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/resource/materialLoader/MaterialLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"

#include <map>
using namespace std;

//-----------------------------------------------------------------------------------
void FPSTextComponent::Intialize( std::map<std::string, std::string> mapParams )
{
	textComponent = (TextComponent*) TextComponent::Create(this->mpGameObject, mapParams);

	textComponent->SetText("0");

}

//-----------------------------------------------------------------------------------
void FPSTextComponent::OnAwake()
{

}

//-----------------------------------------------------------------------------------
void FPSTextComponent::OnUpdate()
{
	char fpsBuffer[5];
	sprintf_s(fpsBuffer, "%d", Time::GetInstance()->GetFPS());
	textComponent->SetText( fpsBuffer );
}
