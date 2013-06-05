#include "platform.h"

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
PS2Renderer::PS2Renderer(RendererConfig config) : PlatformRenderer(config)
{
	draw_initialize(GRAPH_MODE_AUTO , GRAPH_PSM_32, GRAPH_PSM_32);
}


//-----------------------------------------------------------------------------------
// This needs to be factored out.
void PS2Renderer::FakeSceneSetup(RendererConfig config)
{

}

//-----------------------------------------------------------------------------------
void PS2Renderer::SetVertexData(TriangleData triangle)
{

}

//-----------------------------------------------------------------------------------
void PS2Renderer::Clear(Color c)
{
	draw_clear(c.r, c.g, c.b);
}

//-----------------------------------------------------------------------------------
void PS2Renderer::BeginScene()
{
	
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