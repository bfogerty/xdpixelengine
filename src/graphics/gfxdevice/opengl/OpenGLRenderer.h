#ifndef		__OPENGL_RENDERER__
#define		__OPENGL_RENDERER__
#include "core/platform.h"
#include "graphics/PlatformRenderer.h"
#include "graphics/RendererConfig.h"

#ifdef WIN_RELEASE
#include "windows.h"
#endif

#include "external/glad/glad.h"
#include "core/resource/texture2d/Texture2D.h"
#include "core/resource/texture2d/OpenGLTexture2D.h"

class Color;
class TriangleData;

class OpenGLRenderer : public PlatformRenderer
{
public:
	OpenGLRenderer(RendererConfig config);

	virtual void Clear( unsigned int buffers, Color c );
	virtual void UpdateMatricies();
	virtual void BeginScene();
	virtual void EndScene();
	virtual void Present();

	virtual void SetVertexData(Mesh *pMesh);
	virtual void CreateTexture(Texture2D &texture);
	virtual void BindTexture( Texture2D *pTexture );

	// This needs to be factored out.
	virtual void FakeSceneSetup( RendererConfig config );

	//virtual void SetTransform( MATRIX_TRANSFORM_STATE_TYPE ts, Matrix4x4 mat);

	virtual void DrawDebugLine(Vector3 *start, Vector3 *end, Color *color);

	~OpenGLRenderer();

protected:

#ifdef WIN_RELEASE
	void InitializeForWindows( RendererConfig config );
	void SetupGLCore(HWND hWnd);
	void SetupOldGL(HWND hWnd);
	HDC mHdc;
	HGLRC mpDev;
#endif

};

#endif