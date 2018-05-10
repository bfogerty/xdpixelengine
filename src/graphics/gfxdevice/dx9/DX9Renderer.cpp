#include "core/platform.h"

#ifdef COMPILE_DX9_RENDERER
#include "external/directx/Include/d3dx9.h"
#include "graphics/gfxdevice/dx9/DX9Renderer.h"
#include "graphics/Color.h"
#include "core/math/Vector3.h"
#include "core/mesh/Mesh.h"
#include "core/math/MathHelper.h"
#include "core/math/Matrix4x4.h"

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

	// Create Buffer Type Mappings
	mBufferTypeMap[BT_COLOR] = D3DCLEAR_TARGET;
	mBufferTypeMap[BT_DEPTH] = D3DCLEAR_ZBUFFER;
	mBufferTypeMap[BT_STENCIL] = D3DCLEAR_STENCIL;
}

//-----------------------------------------------------------------------------------
// This needs to be factored out.
void DX9Renderer::FakeSceneSetup(RendererConfig config)
{
	mpDev->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );       
	mpDev->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );   
	mpDev->SetRenderState( D3DRS_LIGHTING, FALSE );
}

//-----------------------------------------------------------------------------------
void *DX9Renderer::GetDeviceContext()
{
	return (void*) mpDev;
}

struct CUSTOMVERT
{
	float x,y,z;
	float nx, ny, nz;
	DWORD color;
	float u,v;

	CUSTOMVERT( Vector3 verts, Vector3 normal, Color color, Vector3 texCoord)
	{
		x = verts.x();
		y = verts.y();
		z = verts.z();

		nx = normal.x();
		ny = normal.y();
		nz = normal.z();

		this->color = D3DXCOLOR(color.r,color.g, color.b, color.a);

		u = texCoord.x();
		v = texCoord.y();
	}
};

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexData(Mesh *pMesh)
{
	//SetVertexDataViaSystemMemory(triangle);
	SetVertexDataViaVertexBuffer( pMesh );
}

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexDataViaSystemMemory(TriangleData triangle)
{
	CUSTOMVERT t[] = 
	{
		CUSTOMVERT(triangle.verts[0], triangle.normals[0], triangle.colors[0], triangle.uvs[0]),
		CUSTOMVERT(triangle.verts[1], triangle.normals[1], triangle.colors[1], triangle.uvs[1]),
		CUSTOMVERT(triangle.verts[2], triangle.normals[2], triangle.colors[2], triangle.uvs[2])
	};

	mpDev->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	mpDev->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 1, t, sizeof(CUSTOMVERT));
}

//-----------------------------------------------------------------------------------
void* DX9Renderer::CreateVertexBuffer(unsigned int triangleCount)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;

	const unsigned int bufferSizeInBytes = triangleCount * sizeof(CUSTOMVERT) * 3;

	mpDev->CreateVertexBuffer(bufferSizeInBytes,
		D3DUSAGE_WRITEONLY,
		D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1,
		D3DPOOL_DEFAULT,
		&pVertexBuffer,
		NULL);

	return pVertexBuffer;
}

//-----------------------------------------------------------------------------------
void DX9Renderer::FreeVertexBuffer(void* pVertexBuffer)
{
	LPDIRECT3DVERTEXBUFFER9 pBuffer = static_cast<LPDIRECT3DVERTEXBUFFER9>(pVertexBuffer);
	pBuffer->Release();
}

//-----------------------------------------------------------------------------------
void DX9Renderer::UploadMeshToGPU(Mesh *pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = static_cast<LPDIRECT3DVERTEXBUFFER9>(pMesh->GetVertexBuffer());
	CUSTOMVERT *pVerts;

	const unsigned int bufferSizeInBytes = pMesh->triangleData.size() * sizeof(CUSTOMVERT) * 3;

	pVertexBuffer->Lock(0, bufferSizeInBytes, (void**)&pVerts, 0);
	for (unsigned int triangleIndex = 0; triangleIndex < pMesh->triangleData.size(); ++triangleIndex)
	{
		for (int i = 0; i < 3; ++i)
		{
			Vector3 points = pMesh->triangleData[triangleIndex]->verts[i];
			Vector3 normal = pMesh->triangleData[triangleIndex]->normals[i];
			Color color = pMesh->triangleData[triangleIndex]->colors[i];
			Vector3 texCoord = pMesh->triangleData[triangleIndex]->uvs[i];
			*pVerts++ = CUSTOMVERT(points, normal, color, texCoord);
		}
	}

	pVertexBuffer->Unlock();
}

//-----------------------------------------------------------------------------------
void DX9Renderer::DrawMesh(Mesh *pMesh)
{
	LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = static_cast<LPDIRECT3DVERTEXBUFFER9>(pMesh->GetVertexBuffer());
	mpDev->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	mpDev->SetStreamSource(0, pVertexBuffer, 0, sizeof(CUSTOMVERT));
	mpDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pMesh->triangleData.size());
}

//-----------------------------------------------------------------------------------
void DX9Renderer::SetVertexDataViaVertexBuffer(Mesh *pMesh)
{
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer = NULL;
	CUSTOMVERT *pVerts;

	const unsigned int bufferSizeInBytes = pMesh->triangleData.size() * sizeof(CUSTOMVERT) * 3;

	//if (pVertexBuffer == NULL)
	{
		mpDev->CreateVertexBuffer(bufferSizeInBytes,
			D3DUSAGE_WRITEONLY,
			D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1,
			D3DPOOL_DEFAULT,
			&pVertexBuffer,
			NULL);
	}

	pVertexBuffer->Lock(0, bufferSizeInBytes, (void**) &pVerts, 0);
	for (unsigned int triangleIndex = 0; triangleIndex < pMesh->triangleData.size(); ++triangleIndex)
	{
		for (int i = 0; i < 3; ++i)
		{
			Vector3 points = pMesh->triangleData[triangleIndex]->verts[i];
			Vector3 normal = pMesh->triangleData[triangleIndex]->normals[i];
			Color color = pMesh->triangleData[triangleIndex]->colors[i];
			Vector3 texCoord = pMesh->triangleData[triangleIndex]->uvs[i];
			*pVerts++ = CUSTOMVERT(points, normal, color, texCoord);
		}
	}

	pVertexBuffer->Unlock();

	mpDev->SetFVF(D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	mpDev->SetStreamSource(0, pVertexBuffer, 0, sizeof(CUSTOMVERT));
	mpDev->DrawPrimitive(D3DPT_TRIANGLELIST, 0, pMesh->triangleData.size());
}

//-----------------------------------------------------------------------------------
void DX9Renderer::Clear( unsigned int buffers, Color c)
{
	unsigned int FinalBuffers = 0;

	FinalBuffers |= ( PlatformRenderer::BT_COLOR & buffers) != 0 ? mBufferTypeMap[BT_COLOR] : 0;
	FinalBuffers |= ( PlatformRenderer::BT_DEPTH & buffers) != 0 ? mBufferTypeMap[BT_DEPTH] : 0;
	FinalBuffers |= ( PlatformRenderer::BT_STENCIL & buffers) != 0 ? mBufferTypeMap[BT_STENCIL] : 0;

	mpDev->Clear(0,NULL, FinalBuffers, D3DCOLOR_COLORVALUE(c.r, c.g, c.b, c.a) ,1.0f, 0);
}

//-----------------------------------------------------------------------------------
void DX9Renderer::UpdateMatricies()
{
	D3DXMATRIX d3dMat(mMatProjection.mMatrix);
	mpDev->SetTransform(D3DTS_PROJECTION, &d3dMat);

	d3dMat = mMatView.mMatrix;
	mpDev->SetTransform(D3DTS_VIEW, &d3dMat);

	d3dMat = mMatWorld.mMatrix;
	mpDev->SetTransform(D3DTS_WORLD, &d3dMat);
}

//-----------------------------------------------------------------------------------
void DX9Renderer::BeginScene()
{

	//mpDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	//mpDev->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );

	mpDev->BeginScene();
}

//-----------------------------------------------------------------------------------
void DX9Renderer::CreateTexture(Texture2D &texture)
{
	UCHAR r, g, b;
	UINT *pDest;
	unsigned int nRow, nPixel;
	D3DLOCKED_RECT d3dRect;

	DX9Texture2D *pTexture = static_cast<DX9Texture2D*>(&texture);
	
	mpDev->CreateTexture(pTexture->Width,pTexture->Height,0,D3DUSAGE_DYNAMIC,D3DFMT_X8R8G8B8,D3DPOOL_DEFAULT, &pTexture->mpTexture, NULL);
	pTexture->mpTexture->LockRect(0,&d3dRect,0,0);

	d3dRect.Pitch >>= 2;

	// copy the image
	unsigned char *pSrc = (unsigned char *)pTexture->data;
	for (nRow = 0; nRow < pTexture->Height; nRow++)
	{
		// set destination pointer for this row
		pDest = (UINT*)d3dRect.pBits + (nRow + 0) * d3dRect.Pitch + 0;

		// copy the row
		for (nPixel = 0; nPixel < pTexture->Width; nPixel++)
		{
			// extract pixel data

			r = *pSrc++;
			g = *pSrc++;
			b = *pSrc++;

			// write color word to texture

			(*pDest++) = 0xFF000000 | (r << 16) | (g << 8) | b;
		}
	}

	pTexture->mpTexture->UnlockRect(0);
}

//-----------------------------------------------------------------------------------
void DX9Renderer::BindTexture( Texture2D *pTexture )
{
	if( pTexture != 0)
	{
		DX9Texture2D *pDX9Texture = static_cast<DX9Texture2D*>(pTexture);
		mpDev->SetTexture(0, pDX9Texture->mpTexture);
	}
	else
	{
		mpDev->SetTexture(0, 0);
	}
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