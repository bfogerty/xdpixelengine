#include "PlatformRenderer.h"

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

class GameObject;
struct RendererConfig;

class RenderEngine
{
public:

	RenderEngine( RendererConfig config );
	~RenderEngine();

	void Render(GameObject *pGameObject);

protected:

	void RenderGameObject( GameObject *pGameObject );

	PlatformRenderer *mRenderer;
	RendererConfig mConfig;
};