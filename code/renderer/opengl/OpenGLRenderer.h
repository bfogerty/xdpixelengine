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
#include "../../core/resource/texture2d/Texture2D.h"
#include "../../core/resource/texture2d/OpenGLTexture2D.h"

class Color;
class TriangleData;

class OpenGLRenderer : public PlatformRenderer
{
public:
	OpenGLRenderer(RendererConfig config);

	virtual void Clear( unsigned int buffers, Color c );
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(TriangleData triangle);
	virtual void CreateTexture(Texture2D &texture);
	virtual void BindTexture( Texture2D *pTexture );

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