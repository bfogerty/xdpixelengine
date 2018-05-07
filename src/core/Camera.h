#ifndef __CAMERA__
#define __CAMERA__
#include "core/GameObject.h"
#include "core/GameObjectComponent.h"
#include "renderer/Color.h"
#include <vector>
using namespace std;

class PlatformRenderer;

class Camera : public GameObjectComponent
{
public:

	enum CameraType
	{
		Perspective = 0,
		Orthogonal
	};

	float mFov;
	float mAspectRatio;
	float mNear;
	float mFar;
	float mWidth;
	float mHeight;
	Color BackGroundColor;
	unsigned int BuffersToClear;
	unsigned int Depth;
	CameraType CameraType;
	unsigned int CullLayerMask;

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams );

	Camera( GameObject *pGameObject );

	void RenderScene( PlatformRenderer *pRenderer, GameObject *pGameObject );
	void RenderGameObject( PlatformRenderer *pRenderer, GameObject *pGameObject );

	void RenderMesh( PlatformRenderer *pRenderer, GameObject *pGameObject );

	vector<GameObject*> GetRenderableGameObjectList( GameObject *pGameObject );
	vector<GameObject*> GetRenderableGameObjectList( GameObject *pGameObject, vector<GameObject*> *gameObjectList );

	static bool SortByCameraDepth( Camera* c1, Camera *c2 );

	static bool SortByDistanceFromCamera( GameObject* g1, GameObject *g2 );

protected:
	void BuildMatricies(PlatformRenderer *pRenderer);
	static Camera *ActiveCamera;

};


#endif