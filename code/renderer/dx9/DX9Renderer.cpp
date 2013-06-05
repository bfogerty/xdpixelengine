#include "platform.h"

#ifdef DX9_RENDERER
#include <d3dx9.h>
#include "DX9Renderer.h"
#include "../Color.h"
#include "../../core/math/Vector3.h"
#include "../core/mesh/Mesh.h"
#include "../../core/math/MathHelper.h"

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

	//mpDev->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);

	FakeSceneSetup(config);
}

//-----------------------------------------------------------------------------------
// This needs to be factored out.
void DX9Renderer::FakeSceneSetup(RendererConfig config)
{

	D3DVERTEXELEMENT9 vertexDeclaration[] = 
	{
		{0,  0, D3DDECLTYPE_FLOAT3,   D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0}, 
		{0, 12, D3DDECLTYPE_D3DCOLOR, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_COLOR,    0}, 
		D3DDECL_END()
	};

	LPDIRECT3DVERTEXDECLARATION9 _vertexDeclaration = 0; 
	mpDev->CreateVertexDeclaration( vertexDeclaration, &_vertexDeclaration ); 
	mpDev->SetVertexDeclaration( _vertexDeclaration );

	D3DXMATRIX mtxPerspective;
	D3DXMatrixIdentity(&mtxPerspective);
	D3DXMatrixPerspectiveFovLH(&mtxPerspective, MathHelper::PI * 45.0f / 180, mfAspectRatio, 0.01f, 1000.0f);

	mpDev->SetTransform(D3DTS_PROJECTION, &mtxPerspective);
	mpDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	D3DXMATRIX mtxView;
	D3DXMatrixIdentity(&mtxView);
	mpDev->SetTransform(D3DTS_VIEW, &mtxView);

	D3DXMATRIX mtxWorld;
	D3DXMatrixIdentity(&mtxWorld);
	mpDev->SetTransform(D3DTS_WORLD, &mtxWorld);

	mpDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );       
	mpDev->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );   
	mpDev->SetRenderState( D3DRS_LIGHTING, FALSE );
}

struct CUSTOMVERT
{
	float x,y,z;
	DWORD color;
};

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexData(TriangleData triangle)
{
	CUSTOMVERT t[] = 
	{
		{triangle.verts[0].x,triangle.verts[0].y,triangle.verts[0].z,D3DXCOLOR(triangle.colors[0].r,triangle.colors[0].g,triangle.colors[0].b,triangle.colors[0].a)},
		{triangle.verts[1].x,triangle.verts[1].y,triangle.verts[1].z,D3DXCOLOR(triangle.colors[1].r,triangle.colors[1].g,triangle.colors[1].b,triangle.colors[1].a)},
		{triangle.verts[2].x,triangle.verts[2].y,triangle.verts[2].z,D3DXCOLOR(triangle.colors[2].r,triangle.colors[2].g,triangle.colors[2].b,triangle.colors[2].a)},
	};

	mpDev->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	mpDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, t, sizeof(CUSTOMVERT));
}

//-----------------------------------------------------------------------------------
void DX9Renderer::Clear(Color c)
{
	mpDev->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_COLORVALUE(c.r, c.g, c.b, c.a) ,1.0f,0);	
}

//-----------------------------------------------------------------------------------
void DX9Renderer::BeginScene()
{
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