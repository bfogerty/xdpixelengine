#include "core/Engine.h"
#include "core/config/EngineConfig.h"
#include "core/GameObject.h"
#include "core/GameObjectComponent.h"
#include "core/Transform.h"
#include "core/math/Vector3.h"
#include "core/time/Time.h"
#include "core/math/Matrix4x4.h"
#include "core/input/Input.h"
#include "graphics/DebugGfx.h"
#include "game/GameMain.h"
#include <iostream>

using namespace std;

unsigned int Engine::TotalFramesSinceStartup = 0;

Engine::Engine() : pRenderEngine(0)
{
	TotalFramesSinceStartup = 0;

	Matrix4x4 mat;

	EngineConfig::renderConfig.WindowHandle = EngineConfig::WindowHandle;
	
	RenderEngine::GetInstance()->Initialize(EngineConfig::renderConfig);
	
	Input::Inst()->Initialize();

	mpRootGameObject = new GameObject("root");
	mpRootGameObject->AddComponent( static_cast<GameObjectComponent*>( new GameMain(mpRootGameObject) ) );

	DebugGfx::Initialize(mpRootGameObject);

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
		DebugGfx::Reset();
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
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->gameObject;
		UpdateGameObject(pChild);
	}
}