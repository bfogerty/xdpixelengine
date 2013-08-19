#include "Engine.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Transform.h"
#include "math/Vector3.h"
#include "time/Time.h"
#include "math/Matrix4x4.h"
#include <iostream>
#include "input/Input.h"
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

	// TODO: We shouldn't use a define to determine which
	// Rendering API to use.  This should come from a config
	// file when we have config file tech.
#ifdef USE_DX9_RENDERER
	renderConfig.RenderAPI = RendererConfig::DX9;
#elif USE_OPENGL_RENDERER
	renderConfig.RenderAPI = RendererConfig::OPENGL;
#endif
	
	RenderEngine::GetInstance()->Initialize(renderConfig);
	
	Input::Inst()->Initialize();

	mpRootGameObject = new GameObject("root");
	mpRootGameObject->AddComponent( static_cast<GameObjectComponent*>( new GameMain(mpRootGameObject) ) );

}

Engine::~Engine()
{
	delete mpRootGameObject;
	mpRootGameObject = NULL;
}

void Engine::Update()
{
	Time::GetInstance()->Start();

	if( mpRootGameObject != 0 )
	{
		UpdateGameObject(mpRootGameObject);
		RenderEngine::GetInstance()->Render(mpRootGameObject);
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
	pGameObject->mpTransform->Update();

	int iChildCount = pGameObject->mpTransform->mChildren.size();
	for(int i=0; i< iChildCount; ++i)
	{
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
		UpdateGameObject(pChild);
	}
}