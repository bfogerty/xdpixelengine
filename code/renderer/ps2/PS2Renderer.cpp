#ifdef PS2_RELEASE

#include "PS2Renderer.h"
#include <tamtypes.h>
#include <kernel.h>
#include <sifrpc.h>
#include <loadfile.h>
#include <stdio.h>
#include <dma.h>
#include <draw.h>
#include <graph.h>
#include <malloc.h>
#include <math3d.h>
#include <packet.h>
#include <string.h>


//-----------------------------------------------------------------------------------
PS2Renderer::PS2Renderer(RendererConfig config)
{
	draw_initialize(GRAPH_MODE_AUTO , GRAPH_PSM_32, GRAPH_PSM_32);
}


//-----------------------------------------------------------------------------------
// This needs to be factored out.
void PS2Renderer::FakeSceneSetup(RendererConfig config)
{
	glViewport(0, 0, (GLsizei)config.ScreenWidth, (GLsizei)config.ScreenHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, mfAspectRatio, 0.01f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//-----------------------------------------------------------------------------------
void PS2Renderer::SetVertexData(TriangleData triangle)
{
	for( int i=0; i<3; ++i)
	{
		glVertex3f(triangle.verts[i].x,triangle.verts[i].y,triangle.verts[i].z);
		glColor4d(	(GLdouble)triangle.colors[i].r, 
			(GLdouble)triangle.colors[i].g, 
			(GLdouble)triangle.colors[i].b, 
			(GLdouble)triangle.colors[i].a );
	}
}

//-----------------------------------------------------------------------------------
void PS2Renderer::Clear(Color c)
{
	draw_clear(c.r, c.g, c.b);
}

//-----------------------------------------------------------------------------------
void PS2Renderer::BeginScene()
{
	glBegin(GL_TRIANGLES);
}

//-----------------------------------------------------------------------------------
void PS2Renderer::EndScene()
{

}

//-----------------------------------------------------------------------------------
void PS2Renderer::Present()
{
	graph_wait_vsync();
	draw_swap();

}

PS2Renderer::~PS2Renderer()
{

}

#endif