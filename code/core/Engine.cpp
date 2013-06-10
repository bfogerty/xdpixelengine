#include "Engine.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Transform.h"
#include "math/Vector3.h"
#include "time/Time.h"
#include "math/Matrix4x4.h"
#include <iostream>
#include "../game/GameMain.h"
//#include "../game/RenderTestComponent.h"

using namespace std;

unsigned int Engine::TotalFramesSinceStartup = 0;

Engine::Engine(EngineConfig config) : pRenderEngine(0)
{
	TotalFramesSinceStartup = 0;

	// Test
	//mpGameObject = new GameObject("Test");
	//mpGameObject->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(mpGameObject) ) );

	Matrix4x4 mat;

	RendererConfig renderConfig;
	renderConfig.FullScreen = false;
	renderConfig.ScreenWidth = 800;
	renderConfig.ScreenHeight = 600;
	renderConfig.WindowHandle = config.WindowHandle;
	renderConfig.RenderAPI = RendererConfig::OPENGL;
	pRenderEngine = new RenderEngine( renderConfig );

	mpRootGameObject = new GameObject("root");
	mpRootGameObject->AddComponent( static_cast<GameObjectComponent*>( new GameMain(mpRootGameObject) ) );

}

Engine::~Engine()
{
	delete mpRootGameObject;
	mpRootGameObject = NULL;

	if( pRenderEngine != NULL )
	{
		delete pRenderEngine;
		pRenderEngine = NULL;
	}

}

void Engine::Update()
{
	Time::GetInstance()->Start();

	if( mpRootGameObject != NULL )
	{
		UpdateGameObject(mpRootGameObject);
		pRenderEngine->Render(mpRootGameObject);
	}

	Time::GetInstance()->End();
	++TotalFramesSinceStartup;
}


void Engine::UpdateGameObject( GameObject *pGameObject )
{
	if( !pGameObject )
	{
		return;
	}

	pGameObject->OnUpdate();

	int iChildCount = pGameObject->mpTransform->mChildren.size();
	for(int i=0; i< iChildCount; ++i)
	{
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
		UpdateGameObject(pChild);
	}
}