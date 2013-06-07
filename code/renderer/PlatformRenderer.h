#ifndef __PLATFORM_RENDERER__
#define __PLATFORM_RENDERER__
#include "RendererConfig.h"

class Color;
class Vector3;
class TriangleData;
class Matrix4x4;

class PlatformRenderer
{

public:

	enum MATRIX_TRANSFORM_STATE_TYPE
	{
		TS_PROJECTION = 0,
		TS_VIEW,
		TS_WORLD,
	};

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

	virtual void SetTransform( MATRIX_TRANSFORM_STATE_TYPE ts, Matrix4x4 mat);

protected:
	float mfAspectRatio;

};

#endif