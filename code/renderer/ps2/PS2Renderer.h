#ifndef		__PS2_RENDERER__
#define		__PS2__RENDERER__
#include "platform.h"
#include "PlatformRenderer.h"
#include "RendererConfig.h"

class Color;
class TriangleData;

#ifdef PS2_RELEASE
class PS2Renderer : public PlatformRenderer
{
public:
	PS2Renderer(RendererConfig config);

	virtual void Clear( Color c );
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(TriangleData triangle);

	// This needs to be factored out.
	virtual void FakeSceneSetup( RendererConfig config );

	~PS2Renderer();

protected:

};
#endif

#endif