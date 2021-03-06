#include "core/GameObjectComponent.h"
#include "core/GameObject.h"

#include "core/Camera.h"
#include "game/ObjLoaderTestComponent.h"
#include "game/MoverComponent.h"
#include "game/TextComponent.h"
#include "game/RenderTestComponent.h"
#include "game/FPCameraControllerComponent.h"
#include "game/FullScreenQuadComponent.h"
#include "game/MeshComponent.h"
#include "game/AutoRotateComponent.h"
#include "game/MaterialComponent.h"
#include "game/FPSTextComponent.h"
#include "game/PlaneShadowComponent.h"
#include "game/AbmComponent.h"

std::map<std::string, GameObjectComponent::ComponentClassPointer> GameObjectComponent::mapComponents;

GameObjectComponent::ComponentClassPointer GameObjectComponent::GetClass( std::string className )
{
	if( mapComponents.empty() )
	{
		mapComponents["ObjLoaderTestComponent"] = ObjLoaderTestComponent::Create;
		mapComponents["MoverComponent"] = MoverComponent::Create;
		mapComponents["TextComponent"] = TextComponent::Create;
		mapComponents["RenderTestComponent"] = RenderTestComponent::Create;
		mapComponents["Camera"] = Camera::Create;
		mapComponents["FPCameraControllerComponent"] = FPCameraControllerComponent::Create;
		mapComponents["FullScreenQuadComponent"] = FullScreenQuadComponent::Create;
		mapComponents["MeshComponent"] = MeshComponent::Create;
		mapComponents["AutoRotateComponent"] = AutoRotateComponent::Create;
		mapComponents["MaterialComponent"] = MaterialComponent::Create;
		mapComponents["FPSTextComponent"] = FPSTextComponent::Create;
		mapComponents["PlaneShadowComponent"] = PlaneShadowComponent::Create;
		mapComponents["AbmComponent"] = AbmComponent::Create;
	}

	return mapComponents[ className ];
}

GameObjectComponent::GameObjectComponent( GameObject *pGameObject ) 
: mpGameObject(pGameObject)
{

}

GameObjectComponent::~GameObjectComponent()
{

}

void GameObjectComponent::OnAwake()
{

}

void GameObjectComponent::OnStart()
{

}

void GameObjectComponent::OnUpdate()
{

}

void GameObjectComponent::OnEnable()
{

}

void GameObjectComponent::OnDisable()
{

}

void GameObjectComponent::OnPreRender()
{

}

void GameObjectComponent::OnPostRender()
{

}

void GameObjectComponent::OnRenderObject()
{

}

