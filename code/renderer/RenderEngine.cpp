#include "platform.h"
#include "RenderEngine.h"
#include "Color.h"
#include "GameObject.h"
#include "../core/math/Matrix4x4.h"
#include "../core/math/MathHelper.h"
#include "../core/Transform.h"

RenderEngine* RenderEngine::mpInstance = (RenderEngine*)0;

RenderEngine* RenderEngine::GetInstance()
{
	if( mpInstance == 0 )
	{
		mpInstance = new RenderEngine();
	}

	return mpInstance;
}

RenderEngine::RenderEngine()
{

}

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

	/*
	Matrix4x4 matProjection;
	matProjection.SetPerspectiveFovLH(45.0f * MathHelper::Deg2Rad, mConfig.GetAspectRatio(), 0.00f, 10000.0f);
	mRenderer->SetTransform(PlatformRenderer::TS_PROJECTION, matProjection);

	Matrix4x4 matView;
	matView.SetIdentity();
	mRenderer->SetTransform(PlatformRenderer::TS_VIEW, matView);

	Matrix4x4 matWorld;
	matWorld.SetIdentity();
	mRenderer->SetTransform(PlatformRenderer::TS_WORLD, matWorld);
	*/

	mRenderer->FakeSceneSetup(mConfig);

}

RenderEngine::~RenderEngine()
{

}

void RenderEngine::AddCamera(Camera *camera)
{
	Cameras.push_back(camera);
}

void RenderEngine::Render( GameObject *pGameObject )
{
	if( !mRenderer && Cameras.size() > 0 )
	{
		return;
	}

	Cameras[0]->RenderScene(mRenderer, pGameObject);
}

void RenderEngine::RenderGameObject( GameObject *pGameObject )
{
	bool CanRenderGameObject = true;

	if( !pGameObject )
	{
		return;
	}

	// Can we render the game object?
	if( !pGameObject->mMesh || 
		pGameObject->mMesh->verticies.size() <= 0 )
	{
		CanRenderGameObject = false;
	}

	// If we can't render the game object,
	// we should try to render its children.
	if( !CanRenderGameObject )
	{
		int iChildCount = pGameObject->mpTransform->mChildren.size();
		for(int i=0; i< iChildCount; ++i)
		{
			GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
			RenderGameObject( pChild );
		}
		return;
	}

	// Bind the GameObject's texture if it has one.
	if(pGameObject->pTexture)
	{
		mRenderer->BindTexture(pGameObject->pTexture);
	}

	mRenderer->SetTransform(PlatformRenderer::TS_WORLD, 
		pGameObject->mpTransform->mMatWorld);

	mRenderer->BeginScene();

	//   ... Draw Here ...

	int iNumberOfTriangles = pGameObject->mMesh->triangleData.size();
	for( int i=0; i< iNumberOfTriangles; ++i )
	{
		mRenderer->SetVertexData(*pGameObject->mMesh->GetTriangleData(i));
	}
	mRenderer->EndScene();

	// Unbind the texture if one was given.
	mRenderer->BindTexture(0);

	int iChildCount = pGameObject->mpTransform->mChildren.size();
	for(int i=0; i< iChildCount; ++i)
	{
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
		RenderGameObject( pChild );
	}
}