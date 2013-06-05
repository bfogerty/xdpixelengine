#include "PlatformRenderer.h"
#include "Color.h"
#include "../core/math/Vector3.h"
#include "../core/mesh/Mesh.h"

PlatformRenderer::PlatformRenderer(RendererConfig config)
{
	mfAspectRatio = (float)(config.ScreenWidth) / config.ScreenHeight;
}

PlatformRenderer::~PlatformRenderer()
{

}


// This needs to be factored out.
void PlatformRenderer::FakeSceneSetup( RendererConfig config )
{

}

void PlatformRenderer::SetVertexData(TriangleData triangle)
{

}

void PlatformRenderer::Clear( Color c )
{

}

void PlatformRenderer::BeginScene()
{

}

void PlatformRenderer::EndScene()
{

}

void PlatformRenderer::Present()
{

}
