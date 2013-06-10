#ifndef __DX9_RENDERER__
#define __DX9_RENDERER__
#include "platform.h"

#ifdef COMPILE_DX9_RENDERER
#define D3D_DEBUG_INFO
#include "PlatformRenderer.h"
#include "RendererConfig.h"
#include <d3d9.h>
#include <d3dx9.h>

class Color;
class TriangleData;

class DX9Renderer : public PlatformRenderer
{
public:
	DX9Renderer(RendererConfig config);

	virtual void Clear( Color c );
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(TriangleData triangle);

	// This should be factored out
	void FakeSceneSetup(RendererConfig config);

	~DX9Renderer();

protected:

	virtual void SetVertexDataViaSystemMemory(TriangleData triangle);
	virtual void SetVertexDataViaVertexBuffer(TriangleData triangle);


	LPDIRECT3D9 mpD3D9;
	D3DDISPLAYMODE mDisplayMode;
	D3DPRESENT_PARAMETERS mPresentationParams;
	LPDIRECT3DDEVICE9 mpDev;
};

#endif
#endif