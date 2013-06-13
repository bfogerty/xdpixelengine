#ifndef __PLATFORM_RENDERER__
#define __PLATFORM_RENDERER__
#include "../core/platform.h"
#include "RendererConfig.h"
#include "../core/math/Matrix4x4.h"

#ifdef COMPILE_DX9_RENDERER
#include <d3d9.h>
#endif

class Color;
class Vector3;
class TriangleData;
class Matrix4x4;

struct TextureInfo
{
	int iTextureID;

	#ifdef COMPILE_DX9_RENDERER
	LPDIRECT3DTEXTURE9 pDX9Texture;
	#endif
};

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
	virtual TextureInfo *CreateTexture(void *data, int Width, int Height){ return 0; }
	virtual void BindTexture( TextureInfo *pTextureInfo ){};

	// This needs to be factored out.
	virtual void FakeSceneSetup(RendererConfig config);

	virtual Matrix4x4* GetTransform( MATRIX_TRANSFORM_STATE_TYPE ts);
	virtual void SetTransform( MATRIX_TRANSFORM_STATE_TYPE ts, Matrix4x4 mat);

protected:
	float mfAspectRatio;
	Matrix4x4 mMatProjection;
	Matrix4x4 mMatView;
	Matrix4x4 mMatWorld;
};

#endif