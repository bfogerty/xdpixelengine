#ifndef __RENDER_ENGINE__
#define __RENDER_ENGINE__

#include "PlatformRenderer.h"
#include "../core/Camera.h"

#ifdef PS2_RELEASE
#include "ps2/PS2Renderer.h"
#else
#if COMPILE_DX9_RENDERER
#include "dx9/DX9Renderer.h"
#endif
#if COMPILE_OPENGL_RENDERER
#include "opengl/OpenGLRenderer.h"
#endif
#endif

#include <vector>
using namespace std;

class GameObject;
struct RendererConfig;

class RenderEngine
{
public:

	RenderEngine();
	~RenderEngine();

	static RenderEngine *mpInstance;
	static RenderEngine* GetInstance();

	void Initialize(RendererConfig renderConfig);
	void Render(GameObject *pGameObject);

	PlatformRenderer *GetRenderer() { return mRenderer; }

	void AddCamera(Camera *camera);

	RendererConfig* GetRenderConfig() { return &mConfig; } 

protected:

	void RenderGameObject( GameObject *pGameObject );

	PlatformRenderer *mRenderer;
	RendererConfig mConfig;
	vector<Camera*> Cameras;
};


#endif



