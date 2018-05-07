#ifndef __DX9_RENDERER__
#define __DX9_RENDERER__
#include "core/platform.h"

#ifdef COMPILE_DX9_RENDERER
#define D3D_DEBUG_INFO
#include "renderer/PlatformRenderer.h"
#include "renderer/RendererConfig.h"
#include "core/resource/texture2d/Texture2D.h"
#include "core/resource/texture2d/DX9Texture2D.h"
#include "external/directx/Include/d3d9.h"
#include "external/directx/Include/d3dx9.h"

class Color;
class TriangleData;
class Texture2D;
class Mesh;

class DX9Renderer : public PlatformRenderer
{
public:
	DX9Renderer(RendererConfig config);

	virtual void *GetDeviceContext();

	virtual void Clear( unsigned int buffers, Color c );
	virtual void UpdateMatricies();
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(Mesh *pMesh);
	virtual void CreateTexture(Texture2D &texture);
	virtual void BindTexture( Texture2D *pTexture );

	// This should be factored out
	void FakeSceneSetup(RendererConfig config);

	~DX9Renderer();

protected:

	virtual void SetVertexDataViaSystemMemory(TriangleData triangle);
	virtual void SetVertexDataViaVertexBuffer(Mesh *pMesh);
	virtual void* CreateVertexBuffer(unsigned int triangleCount);
	virtual void FreeVertexBuffer(void* pVertexBuffer);
	virtual void UploadMeshToGPU(Mesh *pMesh);
	virtual void DrawMesh(Mesh *pMesh);


	LPDIRECT3D9 mpD3D9;
	D3DDISPLAYMODE mDisplayMode;
	D3DPRESENT_PARAMETERS mPresentationParams;
	LPDIRECT3DDEVICE9 mpDev;
};

#endif
#endif