#include "GameMain.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"

#include "../game/RenderTestComponent.h"
#include "../game/TriangleComponent.h"


//-----------------------------------------------------------------------------------
void GameMain::OnAwake()
{
	// The root should always be at the center of the world.
	mpGameObject->mpTransform->mMatWorld.Translate(Vector3(0.0f, 0.0f, 0.0f));

	// Add Game Specific logic below.
	GameObject *pGameObject = new GameObject("RenderTest0");
	pGameObject->AddComponent( static_cast<GameObjectComponent*>( new TriangleComponent(pGameObject) ) );
	mpGameObject->mpTransform->mChildren.push_back(pGameObject->mpTransform);

	/*
	pGameObject = new GameObject("RenderTest1");
	pGameObject->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(pGameObject) ) );
	mpGameObject->mpTransform->mChildren.push_back(pGameObject->mpTransform);

	pGameObject = new GameObject("RenderTest2");
	pGameObject->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(pGameObject) ) );
	mpGameObject->mpTransform->mChildren.push_back(pGameObject->mpTransform);
	*/
}

//-----------------------------------------------------------------------------------
void GameMain::OnUpdate()
{
	
}