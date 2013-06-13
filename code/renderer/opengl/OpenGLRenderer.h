#ifndef		__OPENGL_RENDERER__
#define		__OPENGL_RENDERER__
#include "platform.h"
#include "PlatformRenderer.h"
#include "RendererConfig.h"

#ifdef WIN_RELEASE
#include "windows.h"
#endif

#include <gl/gl.h>
#include <gl/glu.h>

class Color;
class TriangleData;

class OpenGLRenderer : public PlatformRenderer
{
public:
	OpenGLRenderer(RendererConfig config);

	virtual void Clear( Color c );
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(TriangleData triangle);
	virtual TextureInfo *CreateTexture(void *data, int Width, int Height);
	virtual void BindTexture( TextureInfo *pTextureInfo );

	// This needs to be factored out.
	virtual void FakeSceneSetup( RendererConfig config );

	//virtual void SetTransform( MATRIX_TRANSFORM_STATE_TYPE ts, Matrix4x4 mat);

	~OpenGLRenderer();

protected:

#ifdef WIN_RELEASE
	void InitializeForWindows( RendererConfig config );
	HDC mHdc;
	HGLRC mpDev;
#endif

};

#endif