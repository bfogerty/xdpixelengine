#include "platform.h"

#ifdef OPENGL_RENDERER
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

	FakeSceneSetup(config);
}
#endif

//-----------------------------------------------------------------------------------
// This needs to be factored out.
void OpenGLRenderer::FakeSceneSetup(RendererConfig config)
{
	glViewport(0, 0, (GLsizei)config.ScreenWidth, (GLsizei)config.ScreenHeight);
	
	/*
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, mfAspectRatio, 0.01f, 1000.0f);
	*/

	glMatrixMode(GL_PROJECTION);
	Matrix4x4 matProjection;
	matProjection.SetPerspectiveFovLH(MathHelper::PI * 45.0f / 180, mfAspectRatio, 0.01f, 1000.0f);
	glLoadMatrixf(matProjection.mMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::SetVertexData(TriangleData triangle)
{
	for( int i=0; i<3; ++i)
	{
		glVertex3f(triangle.verts[i].x(),triangle.verts[i].y(),triangle.verts[i].z());
		glColor4d(	(GLdouble)triangle.colors[i].r, 
					(GLdouble)triangle.colors[i].g, 
					(GLdouble)triangle.colors[i].b, 
					(GLdouble)triangle.colors[i].a );
	}
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::Clear(Color c)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(c.r, c.g, c.b, c.a);
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::BeginScene()
{
	glBegin(GL_TRIANGLES);
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