#ifndef __CAMERA__
#define __CAMERA__
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "Color.h"

class PlatformRenderer;

class Camera : public GameObjectComponent
{
public:

	float mFov;
	float mAspectRatio;
	float mNear;
	float mFar;
	Color BackGroundColor;
	unsigned int BuffersToClear;
	unsigned int Depth;

	Camera( GameObject *pGameObject );

	void RenderScene( PlatformRenderer *pRenderer, GameObject *pGameObject );
	void RenderGameObject( PlatformRenderer *pRenderer, GameObject *pGameObject );

	static bool SortByCameraDepth( Camera* c1, Camera *c2 );

protected:
	void BuildMatricies(PlatformRenderer *pRenderer);

};


#endif