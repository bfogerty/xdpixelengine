#include "platform.h"

#ifdef COMPILE_OPENGL_RENDERER
#include "OpenGLRenderer.h"
#include "../Color.h"
#include "../../core/math/Vector3.h"
#include "../core/mesh/Mesh.h"
#include "../../core/math/MathHelper.h"
#include "../../core/math/Matrix4x4.h"

//-----------------------------------------------------------------------------------
OpenGLRenderer::OpenGLRenderer(RendererConfig config) : PlatformRenderer(config)
{

#ifdef WIN_RELEASE
	InitializeForWindows(config);
#endif

	glViewport(0, 0, (GLsizei)config.ScreenWidth, (GLsizei)config.ScreenHeight);
}

//-----------------------------------------------------------------------------------
#ifdef WIN_RELEASE
void OpenGLRenderer::InitializeForWindows( RendererConfig config )
{
	HWND hWnd = (HWND)config.WindowHandle;
	mHdc = GetDC(hWnd);

	PIXELFORMATDESCRIPTOR pfd;
	ZeroMemory(&pfd, sizeof(pfd));
	pfd.nSize = sizeof(pfd);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 24;
	pfd.cDepthBits = 16;
	pfd.iLayerType = PFD_MAIN_PLANE;
	int iFormat = ChoosePixelFormat(mHdc, &pfd);
	SetPixelFormat(mHdc, iFormat, &pfd);

	mpDev = wglCreateContext(mHdc);
	wglMakeCurrent(mHdc, mpDev);

	//FakeSceneSetup(config);
}
#endif

//-----------------------------------------------------------------------------------
// This needs to be factored out.
void OpenGLRenderer::FakeSceneSetup(RendererConfig config)
{	

}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::SetVertexData(TriangleData triangle)
{
	for( int i=0; i<3; ++i)
	{
		// Color must come before vertex,
		// otherwise the color will not be assigned to the correct vertex.
		glColor4d(	(GLdouble)triangle.colors[i].r, 
					(GLdouble)triangle.colors[i].g, 
					(GLdouble)triangle.colors[i].b, 
					(GLdouble)triangle.colors[i].a );

		glTexCoord2d(triangle.uvs[i].x(),triangle.uvs[i].y());

		glVertex3f(triangle.verts[i].x(),triangle.verts[i].y(),triangle.verts[i].z());
	}
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::Clear(Color c)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(c.r, c.g, c.b, c.a);
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::BeginScene()
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(mMatProjection.mMatrix);

	Matrix4x4 matModelView = mMatView * mMatWorld;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(matModelView.mMatrix);

	glBegin(GL_TRIANGLES);
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::CreateTexture(Texture2D &texture)
{
	OpenGLTexture2D *pTexture = static_cast<OpenGLTexture2D*>(&texture);

	int wrap = 1;
	glGenTextures(1, (GLuint*)&pTexture->iTextureID);
	glBindTexture(GL_TEXTURE_2D, pTexture->iTextureID);

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)data);

	//// build our texture mipmaps
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, pTexture->Width, pTexture->Height,
		GL_RGB, GL_UNSIGNED_BYTE, pTexture->data );
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::BindTexture( Texture2D *pTexture )
{
	if( pTexture != 0 )
	{
		OpenGLTexture2D *pOpenGLTexture = static_cast<OpenGLTexture2D*>(pTexture);
		glEnable( GL_TEXTURE_2D );
		glBindTexture( GL_TEXTURE_2D, pOpenGLTexture->iTextureID);
	
	}
	else
	{
		glBindTexture( GL_TEXTURE_2D, 0 );
		glDisable( GL_TEXTURE_2D );
	}
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::EndScene()
{
	glEnd();
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::Present()
{
	SwapBuffers(mHdc);
	glFlush();
}

//-----------------------------------------------------------------------------------
OpenGLRenderer::~OpenGLRenderer()
{

}
#endif