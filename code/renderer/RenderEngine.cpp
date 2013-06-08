#include "platform.h"
#include "RenderEngine.h"
#include "Color.h"
#include "GameObject.h"
#include "../core/math/Matrix4x4.h"
#include "../core/math/MathHelper.h"
#include "../core/Transform.h"

RenderEngine::RenderEngine( RendererConfig config ) : mRenderer(0), mConfig(config)
{

#ifdef PS2_RELEASE
	mRenderer = static_cast<PlatformRenderer*>( new PS2Renderer(mConfig) );
#elif DX9_RENDERER
	mRenderer = static_cast<PlatformRenderer*>( new DX9Renderer( mConfig ) );
#elif OPENGL_RENDERER
	mRenderer = static_cast<PlatformRenderer*>( new OpenGLRenderer( mConfig ) );
#endif

	Matrix4x4 matProjection;
	matProjection.SetPerspectiveFovLH(45.0f * MathHelper::Deg2Rad, mConfig.GetAspectRatio(), 0.01f, 1000.0f);
	mRenderer->SetTransform(PlatformRenderer::TS_PROJECTION, matProjection);

	Matrix4x4 matView;
	matView.SetIdentity();
	mRenderer->SetTransform(PlatformRenderer::TS_VIEW, matView);

	Matrix4x4 matWorld;
	matWorld.SetIdentity();
	mRenderer->SetTransform(PlatformRenderer::TS_WORLD, matWorld);

	mRenderer->FakeSceneSetup(mConfig);
}

RenderEngine::~RenderEngine()
{

}

void RenderEngine::Render( GameObject *pGameObject )
{
	if( !mRenderer )
	{
		return;
	}

	mRenderer->Clear(Color(Color::GRAY));

	RenderGameObject( pGameObject );

	mRenderer->Present();
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


	mRenderer->BeginScene();
	mRenderer->SetTransform(PlatformRenderer::TS_WORLD, 
		pGameObject->mpTransform->mMatWorld);

	//   ... Draw Here ...

	int iNumberOfTriangles = pGameObject->mMesh->triangleData.size();
	for( int i=0; i< iNumberOfTriangles; ++i )
	{
		mRenderer->SetVertexData(*pGameObject->mMesh->GetTriangleData(i));
	}
	mRenderer->EndScene();
}