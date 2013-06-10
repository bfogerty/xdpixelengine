#include "platform.h"

#ifdef COMPILE_DX9_RENDERER
#include <d3dx9.h>
#include "DX9Renderer.h"
#include "../Color.h"
#include "../../core/math/Vector3.h"
#include "../core/mesh/Mesh.h"
#include "../../core/math/MathHelper.h"
#include "../../core/math/Matrix4x4.h"

//-----------------------------------------------------------------------------------
DX9Renderer::DX9Renderer(RendererConfig config) : PlatformRenderer(config)
{
	mpD3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	mpD3D9->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&mDisplayMode);

	// Build Presentation Parameters
	ZeroMemory(&mPresentationParams, sizeof(D3DPRESENT_PARAMETERS));
	mPresentationParams.hDeviceWindow = (HWND)(config.WindowHandle);
	mPresentationParams.SwapEffect = D3DSWAPEFFECT_DISCARD;
	mPresentationParams.MultiSampleType = D3DMULTISAMPLE_NONE;
	mPresentationParams.MultiSampleQuality = 0;
	mPresentationParams.BackBufferFormat = mDisplayMode.Format;
	mPresentationParams.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	mPresentationParams.EnableAutoDepthStencil = true;
	mPresentationParams.AutoDepthStencilFormat = D3DFMT_D24S8;
	mPresentationParams.BackBufferWidth = UINT(config.ScreenWidth);
	mPresentationParams.BackBufferHeight = UINT(config.ScreenHeight);
	mPresentationParams.BackBufferFormat = D3DFMT_A8R8G8B8;
	mPresentationParams.BackBufferCount = 2;
	mPresentationParams.Flags = 0;
	mPresentationParams.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	mPresentationParams.Windowed = !config.FullScreen;

	if( !SUCCEEDED( mpD3D9->CreateDevice(	D3DADAPTER_DEFAULT,
							D3DDEVTYPE_HAL,
							(HWND)config.WindowHandle,
							D3DCREATE_HARDWARE_VERTEXPROCESSING, 
							&mPresentationParams,
							&mpDev)) )
	{
		// Failed to Create Device.
	}
}

//-----------------------------------------------------------------------------------
// This needs to be factored out.
void DX9Renderer::FakeSceneSetup(RendererConfig config)
{
	mpDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );       
	mpDev->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );   
	mpDev->SetRenderState( D3DRS_LIGHTING, FALSE );
}

struct CUSTOMVERT
{
	float x,y,z;
	DWORD color;

	CUSTOMVERT( Vector3 verts, Color color)
	{
		x = verts.x();
		y = verts.y();
		z = verts.z();

		this->color = D3DXCOLOR(color.r,color.g, color.b, color.a);
	}
};

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexData(TriangleData triangle)
{
	SetVertexDataViaSystemMemory(triangle);
	//SetVertexDataViaVertexBuffer( triangle );
}

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexDataViaSystemMemory(TriangleData triangle)
{
	CUSTOMVERT t[] = 
	{
		CUSTOMVERT(triangle.verts[0], triangle.colors[0]),
		CUSTOMVERT(triangle.verts[1], triangle.colors[1]),
		CUSTOMVERT(triangle.verts[2], triangle.colors[2])
	};

	mpDev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	mpDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, t, sizeof(CUSTOMVERT));
}

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexDataViaVertexBuffer(TriangleData triangle)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;
	CUSTOMVERT *pVerts;

	mpDev->CreateVertexBuffer(sizeof(CUSTOMVERT)*6,
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX0,
		D3DPOOL_DEFAULT,
		&pVertexBuffer,
		NULL);

	pVertexBuffer->Lock(0, sizeof(CUSTOMVERT)*3,(void**) &pVerts, 0);
	for(int i=0; i<3; ++i)
	{
		Vector3 points = triangle.verts[i];
		Color color = triangle.colors[i];
		*pVerts++ = CUSTOMVERT(points, color);
	}
	pVertexBuffer->Unlock();

	mpDev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	mpDev->SetStreamSource(0, pVertexBuffer, 0, sizeof(CUSTOMVERT));
	mpDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

//-----------------------------------------------------------------------------------
void DX9Renderer::Clear(Color c)
{
	mpDev->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(c.r, c.g, c.b, c.a) ,1.0f,0);	
}

//-----------------------------------------------------------------------------------
void DX9Renderer::BeginScene()
{
	D3DXMATRIX d3dMat(mMatProjection.mMatrix);
	mpDev->SetTransform(D3DTS_PROJECTION, &d3dMat);

	d3dMat = mMatView.mMatrix;
	mpDev->SetTransform(D3DTS_VIEW, &d3dMat);

	d3dMat = mMatWorld.mMatrix;
	mpDev->SetTransform(D3DTS_WORLD, &d3dMat);

	mpDev->BeginScene();
}

//-----------------------------------------------------------------------------------
void DX9Renderer::EndScene()
{
	mpDev->EndScene();
}

//-----------------------------------------------------------------------------------
void DX9Renderer::Present()
{
	mpDev->Present(NULL,NULL,NULL,NULL);
}

//-----------------------------------------------------------------------------------
DX9Renderer::~DX9Renderer()
{

}

#endif