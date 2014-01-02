#include "Engine.h"
#include "config/EngineConfig.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Transform.h"
#include "math/Vector3.h"
#include "time/Time.h"
#include "math/Matrix4x4.h"
#include <iostream>
#include "input/Input.h"
#include "../game/GameMain.h"

using namespace std;

unsigned int Engine::TotalFramesSinceStartup = 0;

Engine::Engine() : pRenderEngine(0)
{
	TotalFramesSinceStartup = 0;

	Matrix4x4 mat;

	//EngineConfig::renderConfig.FullScreen = false;
	//EngineConfig::renderConfig.ScreenWidth = 800;
	//EngineConfig::renderConfig.ScreenHeight = 600;
	EngineConfig::renderConfig.WindowHandle = EngineConfig::WindowHandle;

	
	RenderEngine::GetInstance()->Initialize(EngineConfig::renderConfig);
	
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