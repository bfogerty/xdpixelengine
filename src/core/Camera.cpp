#include "core/Camera.h"
#include "core/Transform.h"
#include "core/math/MathHelper.h"
#include "graphics/RenderEngine.h"
#include "graphics/PlatformRenderer.h"
#include "graphics/shaders/ShaderProgram.h"
#include "graphics/shaders/ShaderTechnique.h"
#include "graphics/shaders/ShaderPass.h"
#include "graphics/DebugGfx.h"
#include "core/time/Time.h"
#include <vector>
#include <string>
#include <algorithm>

Camera *Camera::ActiveCamera;

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

	sscanf_s( colorStr.c_str(), "%d,%d,%d,%d", &r,&g,&b,&a);
	sscanf_s( fovStr.c_str(), "%f", &fov);
	sscanf_s( nearStr.c_str(), "%f", &n);
	sscanf_s( farStr.c_str(), "%f", &f);
	sscanf_s( bufferClearCodeStr.c_str(), "%d", &bufferClearCode);
	sscanf_s( depthStr.c_str(), "%d", &depth);
	sscanf_s( widthStr.c_str(), "%f", &width);
	sscanf_s( heightStr.c_str(), "%f", &height);
	sscanf_s( cullLayerMaskStr.c_str(), "%d", &cullLayerMask);

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
	posMatrix.Translate( -mpGameObject->mpTransform->position );
	Matrix4x4 rotMatrix = Quaternion::ToMatrix(mpGameObject->mpTransform->rotation);

	Matrix4x4 matWorld = this->mpGameObject->mpTransform->worldMatrix;
	//matWorld = posMatrix * rotMatrix;
	pRenderer->SetTransform(PlatformRenderer::TS_WORLD, matWorld);

	Matrix4x4 matView;
	matView = Matrix4x4::TInverse(	this->mpGameObject->mpTransform->translationMatrix, 
									this->mpGameObject->mpTransform->rotationMatrix );
	pRenderer->SetTransform(PlatformRenderer::TS_VIEW, matView);	
}

//-----------------------------------------------------------------------------------
vector<GameObject*> Camera::GetRenderableGameObjectList( GameObject *pGameObject )
{
	vector<GameObject*> gameObjectList;

	return GetRenderableGameObjectList( pGameObject, &gameObjectList );
}

//-----------------------------------------------------------------------------------
vector<GameObject*> Camera::GetRenderableGameObjectList( GameObject *pGameObject, vector<GameObject*> *gameObjectList )
{

	bool CanRenderGameObject = true;
	if( !pGameObject->mMesh || 
		pGameObject->mMesh->verticies.size() <= 0)
	{
		CanRenderGameObject = false;
	}

	if( !(pGameObject->GetLayer() & CullLayerMask) )
	{
		CanRenderGameObject = false;
	}

	
	// Is the object behind the camera?
	if( CameraType == Perspective )
	{
		Vector3 camFwd = this->mpGameObject->mpTransform->rotation * Vector3(0,0,1.00f);
		camFwd.Normalize();
		Vector3 camPos = this->mpGameObject->mpTransform->position;
		Vector3 fromCamToGo = pGameObject->mpTransform->position - camPos;
		fromCamToGo.Normalize();

		float d = Vector3::Dot(fromCamToGo, camFwd);
		if( d <= 0.00f )
		{
			CanRenderGameObject = false;
		} 
	}

	// If we can't render the game object,
	// we should try to render its children.
	if( CanRenderGameObject )
	{
		gameObjectList->push_back(pGameObject);
	}
	
	int iChildCount = pGameObject->mpTransform->mChildren.size();
	for(int i=0; i< iChildCount; ++i)
	{
		GameObject *pChild = pGameObject->mpTransform->mChildren[i]->gameObject;
		GetRenderableGameObjectList( pChild, gameObjectList );
	}

	return *gameObjectList;
}

//-----------------------------------------------------------------------------------
void Camera::RenderScene( PlatformRenderer *pRenderer, GameObject *pGameObject )
{
	ActiveCamera = this;

	if( !pRenderer )
	{
		ActiveCamera = 0;

		return;
	}

	GameObject *root = pGameObject;
	// Build Array of GameObjects to Render sorted from back to front
	vector<GameObject*> renderObjects = GetRenderableGameObjectList(root);
	std::sort(renderObjects.begin(), renderObjects.end(), SortByDistanceFromCamera);

	BuildMatricies( pRenderer );

	pRenderer->Clear( BuffersToClear, BackGroundColor);

	for( vector<GameObject*>::iterator it = renderObjects.begin(); it != renderObjects.end(); ++it )
	{
		GameObject *renderObj = *it;
		RenderGameObject( pRenderer, renderObj );
	}

	if( ActiveCamera->CameraType == Perspective )
	{
		DebugGfx::Render(pRenderer);
	}

	ActiveCamera = 0;
}

//-----------------------------------------------------------------------------------
void Camera::RenderGameObject( PlatformRenderer *pRenderer, GameObject *pGameObject )
{
	bool CanRenderGameObject = true;

	if( !pGameObject )
	{
		return;
	}

	Material *mat = pGameObject->pMaterial;
	mat->ApplyTextures();


	pRenderer->SetTransform(PlatformRenderer::TS_WORLD, 
		pGameObject->mpTransform->worldMatrix);

	//   ... Draw Here ...
	pRenderer->UpdateMatricies();

	Matrix4x4 *matView = pRenderer->GetTransform( PlatformRenderer::TS_VIEW );
	Matrix4x4 *matProj = pRenderer->GetTransform( PlatformRenderer::TS_PROJECTION );
	Matrix4x4 matWorld = pGameObject->mpTransform->worldMatrix;

	Matrix4x4 matMv = matWorld * *matView;
	Matrix4x4 matMvp = matWorld * *matView * *matProj;
	
	mat->SetFloat("__time", Time::GetInstance()->GetTime());
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
		pRenderer->BeginScene();
		RenderMesh(pRenderer, pGameObject);
		pRenderer->EndScene();
		mat->EndPass(pass);
	}
}

//-----------------------------------------------------------------------------------
void Camera::RenderMesh( PlatformRenderer *pRenderer, GameObject *pGameObject )
{
	if (pGameObject->mMesh->GetVertexBuffer() == NULL)
	{
		pRenderer->SetVertexData(pGameObject->mMesh);
	}
	else
	{
		pRenderer->DrawMesh(pGameObject->mMesh);
	}
}

//-----------------------------------------------------------------------------------
bool Camera::SortByCameraDepth( Camera* c1, Camera *c2 )
{
	bool val = c1->Depth < c2->Depth;
	return val;
}

//-----------------------------------------------------------------------------------
bool Camera::SortByDistanceFromCamera( GameObject* g1, GameObject *g2 )
{
	Vector3 camPos = ActiveCamera->mpGameObject->mpTransform->position;
	Vector3 fromCamToG1 = g1->mpTransform->position - camPos;
	Vector3 fromCamToG2 = g2->mpTransform->position - camPos;

	float g1Dist = Vector3::Distance(camPos, fromCamToG1);
	float g2Dist = Vector3::Distance(camPos, fromCamToG2);

	return g1Dist > g2Dist;
}