#include "GameObjectComponent.h"
#include "GameObject.h"

#include "../game/ObjLoaderTestComponent.h"
#include "../game/MoverComponent.h"
#include "../game/TextComponent.h"
#include "../game/RenderTestComponent.h"

std::map<std::string, GameObjectComponent::ComponentClassPointer> GameObjectComponent::mapComponents;

GameObjectComponent::ComponentClassPointer GameObjectComponent::GetClass( std::string className )
{
	if( mapComponents.empty() )
	{
		mapComponents["ObjLoaderTestComponent"] = ObjLoaderTestComponent::Create;
		mapComponents["MoverComponent"] = MoverComponent::Create;
		mapComponents["TextComponent"] = TextComponent::Create;
		mapComponents["RenderTestComponent"] = RenderTestComponent::Create;
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

