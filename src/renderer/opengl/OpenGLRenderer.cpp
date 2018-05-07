#include "core/platform.h"

#ifdef COMPILE_OPENGL_RENDERER
#include "renderer/opengl/OpenGLRenderer.h"
#include "renderer/Color.h"
#include "core/math/Vector3.h"
#include "core/mesh/Mesh.h"
#include "core/math/MathHelper.h"
#include "core/math/Matrix4x4.h"
#include <assert.h>

void Break(unsigned int glResult)
{
	char buffer[1000];
	//sprintf(buffer, "glGetError() = %d\n%s\n", glResult, gluErrorString(glResult));
	OutputDebugString(buffer);
	assert(glResult == GL_NO_ERROR);
}

#define GL_VERIFY(x) \
x;\
{\
unsigned int glResult = glGetError();\
if (glResult != GL_NO_ERROR) { \
Break(glResult);\
}\
}

//-----------------------------------------------------------------------------------
OpenGLRenderer::OpenGLRenderer(RendererConfig config) : PlatformRenderer(config)
{

	// Create Buffer Type Mappings
	mBufferTypeMap[BT_COLOR] = GL_COLOR_BUFFER_BIT;
	mBufferTypeMap[BT_DEPTH] = GL_DEPTH_BUFFER_BIT;
	mBufferTypeMap[BT_STENCIL] = GL_STENCIL_BUFFER_BIT;

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
	//glBegin(GL_TRIANGLES);
	for( int i=0; i<3; ++i)
	{
		// Color must come before vertex,
		// otherwise the color will not be assigned to the correct vertex.
		(glColor4d(	(GLdouble)triangle.colors[i].r,
					(GLdouble)triangle.colors[i].g, 
					(GLdouble)triangle.colors[i].b, 
					(GLdouble)triangle.colors[i].a ));

		(glTexCoord2d(triangle.uvs[i].x(),triangle.uvs[i].y()));

		(glNormal3f( triangle.normals[i].x(), triangle.normals[i].y(), triangle.normals[i].z() ));

		(glVertex3f(triangle.verts[i].x(),triangle.verts[i].y(),triangle.verts[i].z()));
	}
	//glEnd();
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::Clear( unsigned int buffers, Color c)
{
	unsigned int FinalBuffers = 0;

	FinalBuffers |= ( PlatformRenderer::BT_COLOR & buffers) != 0 ? mBufferTypeMap[BT_COLOR] : 0;
	FinalBuffers |= ( PlatformRenderer::BT_DEPTH & buffers) != 0 ? mBufferTypeMap[BT_DEPTH] : 0;
	FinalBuffers |= ( PlatformRenderer::BT_STENCIL & buffers) != 0 ? mBufferTypeMap[BT_STENCIL] : 0;

	GL_VERIFY(glClear(FinalBuffers));
	GL_VERIFY(glClearColor(c.r, c.g, c.b, c.a));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::UpdateMatricies()
{
	GL_VERIFY(glMatrixMode(GL_PROJECTION));
	GL_VERIFY(glLoadMatrixf(mMatProjection.mMatrix));

	Matrix4x4 matModelView = mMatWorld * mMatView;
	GL_VERIFY(glMatrixMode(GL_MODELVIEW));
	GL_VERIFY(glLoadMatrixf(matModelView.mMatrix));
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::BeginScene()
{
	/*
	glEnable( GL_DEPTH_TEST );

	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(mMatProjection.mMatrix);

	Matrix4x4 matModelView = mMatWorld * mMatView;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(matModelView.mMatrix);
	*/

	(glBegin(GL_TRIANGLES));
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::CreateTexture(Texture2D &texture)
{
	OpenGLTexture2D *pTexture = static_cast<OpenGLTexture2D*>(&texture);

	int wrap = 1;

	GL_VERIFY(glPixelStorei(GL_UNPACK_ALIGNMENT, 1));
	GL_VERIFY(glGenTextures(1, (GLuint*)&pTexture->iTextureID));
	GL_VERIFY(glBindTexture(GL_TEXTURE_2D, pTexture->iTextureID));

	// Begin New

	GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));
	GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
	GL_VERIFY(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST));
	GL_VERIFY(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, pTexture->Width,
                pTexture->Height, 0, GL_RGB, GL_UNSIGNED_BYTE, 
				pTexture->data));
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::BindTexture( Texture2D *pTexture )
{
	if( pTexture != 0 )
	{
		OpenGLTexture2D *pOpenGLTexture = static_cast<OpenGLTexture2D*>(pTexture);
		GL_VERIFY(glEnable( GL_TEXTURE_2D ));
		GL_VERIFY(glBindTexture( GL_TEXTURE_2D, pOpenGLTexture->iTextureID));
	}
	else
	{
		GL_VERIFY(glBindTexture( GL_TEXTURE_2D, 0 ));
		GL_VERIFY(glDisable( GL_TEXTURE_2D ));
	}
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::EndScene()
{
	GL_VERIFY(glEnd());
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::Present()
{
	SwapBuffers(mHdc);
	GL_VERIFY(glFlush());
}

//-----------------------------------------------------------------------------------
void OpenGLRenderer::DrawDebugLine(Vector3 *start, Vector3 *end, Color *color)
{
	UpdateMatricies();

	glLineWidth(2.0f);
	glBegin(GL_LINES);
	// Color must come before vertex,
	// otherwise the color will not be assigned to the correct vertex.
	glColor4d(	(GLdouble)color->r, 
				(GLdouble)color->g, 
				(GLdouble)color->b, 
				(GLdouble)1.0f );

	glVertex3f(start->x(),start->y(),start->z());

	// Color must come before vertex,
	// otherwise the color will not be assigned to the correct vertex.
	glColor4d(	(GLdouble)color->r, 
		(GLdouble)color->g, 
		(GLdouble)color->b, 
		(GLdouble)1.0f );

	glVertex3f(end->x(),end->y(),end->z());
	glEnd();
}

//-----------------------------------------------------------------------------------
OpenGLRenderer::~OpenGLRenderer()
{

}
#endif