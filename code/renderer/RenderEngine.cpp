#include "platform.h"
#include "RenderEngine.h"
#include "Color.h"
#include "GameObject.h"
#include "../core/math/Matrix4x4.h"
#include "../core/math/MathHelper.h"
#include "../core/Transform.h"
#include "../core/Camera.h"
#include <algorithm>

RenderEngine* RenderEngine::mpInstance = (RenderEngine*)0;

//-----------------------------------------------------------------------------------
RenderEngine* RenderEngine::GetInstance()
{
	if( mpInstance == 0 )
	{
		mpInstance = new RenderEngine();
	}

	return mpInstance;
}

//-----------------------------------------------------------------------------------
RenderEngine::RenderEngine()
{

}

//-----------------------------------------------------------------------------------
void RenderEngine::Initialize(RendererConfig config)
{
	mRenderer = 0;
	mConfig = config;


#ifdef PS2_RELEASE
	mRenderer = static_cast<PlatformRenderer*>( new PS2Renderer(mConfig) );
#else
#if COMPILE_DX9_RENDERER
	if( mConfig.RenderAPI == RendererConfig::DX9)
	{
		mRenderer = static_cast<PlatformRenderer*>( new DX9Renderer( mConfig ) );
	}
#endif
#if COMPILE_OPENGL_RENDERER
	if( mConfig.RenderAPI == RendererConfig::OPENGL)
	{
		mRenderer = static_cast<PlatformRenderer*>( new OpenGLRenderer( mConfig ) );
	}
#endif
#endif

	mRenderer->FakeSceneSetup(mConfig);
}

//-----------------------------------------------------------------------------------
RenderEngine::~RenderEngine()
{

}

//-----------------------------------------------------------------------------------
void RenderEngine::AddCamera(Camera *camera)
{
	Cameras.push_back(camera);
	sort(Cameras.begin(), Cameras.end(), Camera::SortByCameraDepth);
	
}

//-----------------------------------------------------------------------------------
void RenderEngine::Render( GameObject *pGameObject )
{
	if( !mRenderer && Cameras.size() > 0 )
	{
		return;
	}

	for( std::vector<Camera*>::iterator it = Cameras.begin(); it != Cameras.end(); ++it )
	{
		Camera *pCamera = static_cast<Camera*>(*it);
		pCamera->RenderScene(mRenderer, pGameObject);
	}

	mRenderer->Present();
}
