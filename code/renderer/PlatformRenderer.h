#ifndef __PLATFORM_RENDERER__
#define __PLATFORM_RENDERER__
#include "../core/platform.h"
#include "RendererConfig.h"
#include "../core/math/Matrix4x4.h"

#ifdef COMPILE_DX9_RENDERER
#include <d3d9.h>
#endif

#include <map>
using namespace std;

class Color;
class Vector3;
class TriangleData;
class Matrix4x4;
class Texture2D;

class PlatformRenderer
{

public:

	enum MATRIX_TRANSFORM_STATE_TYPE
	{
		TS_PROJECTION = 0,
		TS_VIEW,
		TS_WORLD,
	};

	enum BUFFER_TYPE
	{
		BT_COLOR = 1,
		BT_DEPTH = 2,
		BT_STENCIL = 4,
	};

	PlatformRenderer(){};
	PlatformRenderer(RendererConfig config);
	virtual ~PlatformRenderer();

	virtual void *GetDeviceContext();

	virtual void Clear( unsigned int buffers, Color c );
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(TriangleData triangle);
	virtual void CreateTexture(Texture2D &texture){ }
	virtual void BindTexture( Texture2D *pTexture ){};

	// This needs to be factored out.
	virtual void FakeSceneSetup(RendererConfig config);

	virtual Matrix4x4* GetTransform( MATRIX_TRANSFORM_STATE_TYPE ts);
	virtual void SetTransform( MATRIX_TRANSFORM_STATE_TYPE ts, Matrix4x4 mat);

protected:
	float mfAspectRatio;
	Matrix4x4 mMatProjection;
	Matrix4x4 mMatView;
	Matrix4x4 mMatWorld;
	map<unsigned int, unsigned int> mBufferTypeMap;
};

#endif