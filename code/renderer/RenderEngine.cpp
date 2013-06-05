#include "platform.h"
#include "RenderEngine.h"
#include "Color.h"
#include "GameObject.h"

RenderEngine::RenderEngine( RendererConfig config ) : mRenderer(0)
{

#ifdef PS2_RELEASE
	mRenderer = static_cast<PlatformRenderer*>( new PS2Renderer(config) );
#elif DX9_RENDERER
	mRenderer = static_cast<PlatformRenderer*>( new DX9Renderer( config ) );
#elif OPENGL_RENDERER
	mRenderer = static_cast<PlatformRenderer*>( new OpenGLRenderer( config ) );
#endif

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

	if( !pGameObject || !pGameObject->mMesh || pGameObject->mMesh->verticies.size() <= 0 )
	{
		return;
	}

	mRenderer->Clear(Color(Color::GRAY));
	mRenderer->BeginScene();
	//   ... Draw Here ...
	
	int iNumberOfTriangles = pGameObject->mMesh->triangleData.size();
	for( int i=0; i< iNumberOfTriangles; ++i )
	{
		mRenderer->SetVertexData(*pGameObject->mMesh->GetTriangleData(i));
	}

	mRenderer->EndScene();
	mRenderer->Present();
}