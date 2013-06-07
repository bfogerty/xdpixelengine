#include "Engine.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "math/Vector3.h"
#include "time/Time.h"
#include "math/Matrix4x4.h"
#include <iostream>
#include "../game/RenderTestComponent.h"
using namespace std;

unsigned int Engine::TotalFramesSinceStartup = 0;

GameObject *mpGameObject = NULL;


Engine::Engine(EngineConfig config) : pRenderEngine(0)
{
	TotalFramesSinceStartup = 0;

	// Test
	mpGameObject = new GameObject("Test");
	mpGameObject->AddComponent( static_cast<GameObjectComponent*>( new RenderTestComponent(mpGameObject) ) );

	Matrix4x4 mat;

	RendererConfig renderConfig;
	renderConfig.FullScreen = false;
	renderConfig.ScreenWidth = 800;
	renderConfig.ScreenHeight = 600;
	renderConfig.WindowHandle = config.WindowHandle;
	pRenderEngine = new RenderEngine( renderConfig );

}

Engine::~Engine()
{
	delete mpGameObject;
	mpGameObject = NULL;

	if( pRenderEngine != NULL )
	{
		delete pRenderEngine;
		pRenderEngine = NULL;
	}

}

void Engine::Update()
{
	Time::GetInstance()->Start();

	if( mpGameObject != NULL )
	{
		mpGameObject->OnUpdate();
	}

	pRenderEngine->Render(mpGameObject);

	Time::GetInstance()->End();
	++TotalFramesSinceStartup;
}