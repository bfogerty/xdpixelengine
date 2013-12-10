#include "Camera.h"
#include "Transform.h"
#include "math/MathHelper.h"
#include "../renderer/RenderEngine.h"
#include "../renderer/PlatformRenderer.h"

//-----------------------------------------------------------------------------------
Camera::Camera( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
{
	Depth = 0;
	BuffersToClear = PlatformRenderer::BT_COLOR | PlatformRenderer::BT_DEPTH | PlatformRenderer::BT_STENCIL;

	RenderEngine::GetInstance()->AddCamera(this);
}

//-----------------------------------------------------------------------------------
void Camera::BuildMatricies(PlatformRenderer *pRenderer)
{
	Matrix4x4 matProjection;
	matProjection.SetPerspectiveFovLH(mFov * MathHelper::Deg2Rad, mAspectRatio, mNear, mFar);
	//matProjection.SetOrthoLH(0.80f, 0.60f, mNear, mFar);
	pRenderer->SetTransform(PlatformRenderer::TS_PROJECTION, matProjection);

	Matrix4x4 matView;
	matView.SetIdentity();
	matView = Quaternion::ToMatrix(mpGameObject->mpTransform->Rotation);
	matView.SetRow(3, Vector4(mpGameObject->mpTransform->Position, 1.0f));
	matView.Set(0,3, -matView.Get(0,3));
	pRenderer->SetTransform(PlatformRenderer::TS_VIEW, matView);

	Matrix4x4 matWorld;
	matWorld.SetIdentity();
	pRenderer->SetTransform(PlatformRenderer::TS_WORLD, matWorld);
}

//-----------------------------------------------------------------------------------
void Camera::RenderScene( PlatformRenderer *pRenderer, GameObject *pGameObject )
{
	if( !pRenderer )
	{
		return;
	}

	BuildMatricies( pRenderer );

	pRenderer->Clear( BuffersToClear, BackGroundColor);

	RenderGameObject( pRenderer, pGameObject );
}

//-----------------------------------------------------------------------------------
void Camera::RenderGameObject( PlatformRenderer *pRenderer, GameObject *pGameObject )
{
	bool CanRenderGameObject = true;

	if( !pGameObject )
	{
		return;
	}

	// Can we render the game object?
	if( !pGameObject->mMesh || 
		pGameObject->mMesh->verticies.size() <= 0 )
	{
		CanRenderGameObject = false;
	}

	// If we can't render the game object,
	// we should try to render its children.
	if( !CanRenderGameObject )
	{
		int iChildCount = pGameObject->mpTransform->mChildren.size();
		for(int i=0; i< iChildCount; ++i)
		{
			GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
			RenderGameObject( pRenderer, pChild );
		}
		return;
	}

	// Bind the GameObject's texture if it has one.
	if(pGameObject->pTexture)
	{
		pRenderer->BindTexture(pGameObject->pTexture);
	}
	

	pRenderer->SetTransform(PlatformRenderer::TS_WORLD, 
		pGameObject->mpTransform->mMatWorld);

	pRenderer->BeginScene();

	//   ... Draw Here ...

	if( pGameObject->pMaterial )
	{
		pGameObject->pMaterial->BindProgam();
	}

	int iNumberOfTriangles = pGameObject->mMesh->triangleData.size();
	for( int i=0; i< iNumberOfTriangles; ++i )
	{
		pRenderer->SetVertexData(*pGameObject->mMesh->GetTriangleData(i));
	}

	if( pGameObject->pMaterial )
	{
		pGameObject->pMaterial->UnBindProgam();
	}

	pRenderer->EndScene();

	// Unbind the texture if one was given.
	pRenderer->BindTexture(0);

	int iChildCount = pGameObject->mpTransform->mChildren.size();
	for(int i=0; i< iChildCount; ++i)
	{
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
		RenderGameObject( pRenderer, pChild );
	}
}

//-----------------------------------------------------------------------------------
bool Camera::SortByCameraDepth( Camera* c1, Camera *c2 )
{
	return c1->Depth < c2->Depth;
}