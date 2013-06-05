#ifndef __PLATFORM_RENDERER__
#define __PLATFORM_RENDERER__
#include "RendererConfig.h"

class Color;
class Vector3;
class TriangleData;

class PlatformRenderer
{

public:

	PlatformRenderer(){};
	PlatformRenderer(RendererConfig config);
	virtual ~PlatformRenderer();

	virtual void Clear( Color c );
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(TriangleData triangle);

	// This needs to be factored out.
	virtual void FakeSceneSetup(RendererConfig config);


protected:
	float mfAspectRatio;

};

#endif