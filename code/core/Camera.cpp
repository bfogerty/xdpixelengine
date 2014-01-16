#include "Camera.h"
#include "Transform.h"
#include "math/MathHelper.h"
#include "../renderer/RenderEngine.h"
#include "../renderer/PlatformRenderer.h"
#include "../renderer/shaders/ShaderProgram.h"
#include "../renderer/shaders/ShaderTechnique.h"
#include "../renderer/shaders/ShaderPass.h"
#include "time/Time.h"

//-----------------------------------------------------------------------------------
GameObjectComponent* Camera::Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
{
	std::string colorStr = mapParams["color"];
	std::string fovStr = mapParams["fov"];
	std::string nearStr = mapParams["near"];
	std::string farStr = mapParams["far"];
	std::string bufferClearCodeStr = mapParams["bufferclearcode"];
	std::string depthStr = mapParams["depth"];
	std::string typeStr = mapParams["type"];
	std::string widthStr = mapParams["width"];
	std::string heightStr = mapParams["height"];
	std::string cullLayerMaskStr = mapParams["culllayermask"];

	int r,g,b,a = 0;
	float fov = 0.0f;
	float n = 0.0f;
	float f = 0.0f;
	int bufferClearCode = 0;
	int depth = 0;
	float width;
	float height;
	unsigned int cullLayerMask;

	sscanf( colorStr.c_str(), "%d,%d,%d,%d", &r,&g,&b,&a);
	sscanf( fovStr.c_str(), "%f", &fov);
	sscanf( nearStr.c_str(), "%f", &n);
	sscanf( farStr.c_str(), "%f", &f);
	sscanf( bufferClearCodeStr.c_str(), "%d", &bufferClearCode);
	sscanf( depthStr.c_str(), "%d", &depth);
	sscanf( widthStr.c_str(), "%f", &width);
	sscanf( heightStr.c_str(), "%f", &height);
	sscanf( cullLayerMaskStr.c_str(), "%d", &cullLayerMask);

	Camera *camera = new Camera(pGameObject);

	camera->BackGroundColor = Color(Color::Color(r,g,b,a));
	camera->mAspectRatio = RenderEngine::GetInstance()->GetRenderConfig()->GetAspectRatio();
	camera->mFov = fov;
	camera->mNear = n;
	camera->mFar = f;
	camera->BuffersToClear = bufferClearCode;
	camera->Depth = depth;
	camera->mWidth = width;
	camera->mHeight = height;
	camera->CullLayerMask = cullLayerMask;

	if( typeStr == "perspective" )
	{
		camera->CameraType = Perspective;
	}
	else
	{
		camera->CameraType = Orthogonal;
	}

	RenderEngine::GetInstance()->AddCamera(camera);

	return (GameObjectComponent*) camera;
}

//-----------------------------------------------------------------------------------
Camera::Camera( GameObject *pGameObject ) : GameObjectComponent(pGameObject)
{
	Depth = 0;
	BuffersToClear = PlatformRenderer::BT_COLOR | PlatformRenderer::BT_DEPTH | PlatformRenderer::BT_STENCIL;
}

//-----------------------------------------------------------------------------------
void Camera::BuildMatricies(PlatformRenderer *pRenderer)
{
	Matrix4x4 matProjection;

	if( CameraType == Perspective )
	{
		matProjection.SetPerspectiveFovLH(mFov * MathHelper::Deg2Rad, mAspectRatio, mNear, mFar);
	}
	else
	{
		matProjection.SetOrthoLH(mWidth, mHeight, mNear, mFar);
	}
	//matProjection.SetOrthoLH(0.80f, 0.60f, mNear, mFar);
	pRenderer->SetTransform(PlatformRenderer::TS_PROJECTION, matProjection);

	Matrix4x4 posMatrix;
	posMatrix.Translate( mpGameObject->mpTransform->Position );
	Matrix4x4 rotMatrix = Quaternion::ToMatrix(mpGameObject->mpTransform->Rotation);

	Matrix4x4 matWorld = this->mpGameObject->mpTransform->mMatWorld;
	//matWorld = posMatrix * rotMatrix;
	pRenderer->SetTransform(PlatformRenderer::TS_WORLD, matWorld);

	Matrix4x4 matView;
	matView = Matrix4x4::TInverse(	this->mpGameObject->mpTransform->matPosition, 
									this->mpGameObject->mpTransform->matRotation );
	pRenderer->SetTransform(PlatformRenderer::TS_VIEW, matView);

	/*
	Matrix4x4 matView;
	matView.SetIdentity();
	matView = Quaternion::ToMatrix(mpGameObject->mpTransform->Rotation);
	matView.SetRow(3, Vector4(mpGameObject->mpTransform->Position, 1.0f));
	matView.Set(0,3, -matView.Get(0,3));
	pRenderer->SetTransform(PlatformRenderer::TS_VIEW, matView);

	Matrix4x4 matWorld;
	matWorld.SetIdentity();
	*/

	
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

	if( !(pGameObject->GetLayer() & CullLayerMask) )
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
	
	Material *mat = pGameObject->pMaterial;
	mat->ApplyTextures();


	pRenderer->SetTransform(PlatformRenderer::TS_WORLD, 
		pGameObject->mpTransform->mMatWorld);

	pRenderer->BeginScene();

	//   ... Draw Here ...

	Matrix4x4 *matView = pRenderer->GetTransform( PlatformRenderer::TS_VIEW );
	Matrix4x4 *matProj = pRenderer->GetTransform( PlatformRenderer::TS_PROJECTION );
	Matrix4x4 matWorld = pGameObject->mpTransform->mMatWorld;

	Matrix4x4 matMv = matWorld * *matView;
	Matrix4x4 matMvp = matWorld * *matView * *matProj;
	
	mat->SetFloat("__deltaTime", Time::GetInstance()->GetDeltaTime());
	mat->SetFloat("__smoothDeltaTime", Time::GetInstance()->GetSmoothDeltaTime());
	mat->SetMatrix("__model", matWorld);
	mat->SetMatrix("__view", *matView);
	mat->SetMatrix("__projection", *matProj);
	mat->SetMatrix("__modelViewProjection", matMvp);

	if( pGameObject->pTexture != 0 )
	{
		mat->SetTexture("decalSampler", pGameObject->pTexture);
	}

	int passCount = mat->GetPassCount();

	for(int pass = 0; pass < passCount; ++pass)
	{
		mat->BeginPass(pass);
		RenderMesh(pRenderer, pGameObject);
		mat->EndPass(pass);
	}

	pRenderer->EndScene();

	int iChildCount = pGameObject->mpTransform->mChildren.size();
	for(int i=0; i< iChildCount; ++i)
	{
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->mpGameObject;
		RenderGameObject( pRenderer, pChild );
	}
}

//-----------------------------------------------------------------------------------
void Camera::RenderMesh( PlatformRenderer *pRenderer, GameObject *pGameObject )
{
	int iNumberOfTriangles = pGameObject->mMesh->triangleData.size();
	for( int i=0; i< iNumberOfTriangles; ++i )
	{
		pRenderer->SetVertexData(*pGameObject->mMesh->GetTriangleData(i));
	}
}

//-----------------------------------------------------------------------------------
bool Camera::SortByCameraDepth( Camera* c1, Camera *c2 )
{
	bool val = c1->Depth < c2->Depth;
	return val;
}