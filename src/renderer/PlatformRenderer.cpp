#include "PlatformRenderer.h"
#include "Color.h"
#include "../core/math/Vector3.h"
#include "../core/math/Matrix4x4.h"
#include "../core/mesh/Mesh.h"

PlatformRenderer::PlatformRenderer(RendererConfig config)
{
	mfAspectRatio = (float)(config.ScreenWidth) / config.ScreenHeight;

	mBufferTypeMap.clear();
}

PlatformRenderer::~PlatformRenderer()
{

}

void *PlatformRenderer::GetDeviceContext()
{
	return 0;
}

// This needs to be factored out.
void PlatformRenderer::FakeSceneSetup( RendererConfig config )
{

}

void PlatformRenderer::SetVertexData(Mesh *pMesh)
{

}

void* PlatformRenderer::CreateVertexBuffer(unsigned int triangleCount)
{
	return NULL;
}

void PlatformRenderer::FreeVertexBuffer(void* pVertexBuffer)
{

}

void PlatformRenderer::UploadMeshToGPU(Mesh *pMesh)
{

}

void PlatformRenderer::DrawMesh(Mesh *pMesh)
{

}

void PlatformRenderer::Clear( unsigned int buffers, Color c )
{

}

void PlatformRenderer::UpdateMatricies()
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

Matrix4x4* PlatformRenderer::GetTransform( MATRIX_TRANSFORM_STATE_TYPE ts)
{
	switch( ts )
	{
	case PlatformRenderer::TS_PROJECTION:
		{
			return &mMatProjection;
		}
		break;

	case PlatformRenderer::TS_VIEW:
		{
			return &mMatView;
		}
		break;

	case PlatformRenderer::TS_WORLD:
		{
			return &mMatWorld;
		}
		break;
	}

	return 0;
}

void PlatformRenderer::SetTransform( MATRIX_TRANSFORM_STATE_TYPE ts, Matrix4x4 mat)
{
	switch( ts )
	{
	case PlatformRenderer::TS_PROJECTION:
		{
			mMatProjection = mat;
		}
		break;

	case PlatformRenderer::TS_VIEW:
		{
			mMatView = mat;
		}
		break;

	case PlatformRenderer::TS_WORLD:
		{
			mMatWorld = mat;
		}
		break;
	}
}
