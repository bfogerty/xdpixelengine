#include "GameObjectComponent.h"
#include "GameObject.h"

#include "../game/ObjLoaderTestComponent.h"
#include "../game/MoverComponent.h"

std::map<std::string, GameObjectComponent::ComponentClassPointer> GameObjectComponent::mapComponents;

GameObjectComponent::ComponentClassPointer GameObjectComponent::GetClass( std::string className )
{
	if( mapComponents.empty() )
	{
		mapComponents["ObjLoaderTestComponent"] = ObjLoaderTestComponent::Create;
		mapComponents["MoverComponent"] = MoverComponent::Create;
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

