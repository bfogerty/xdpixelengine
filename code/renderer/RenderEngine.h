#include "PlatformRenderer.h"

#ifdef PS2_RELEASE
#include "ps2/PS2Renderer.h"
#elif DX9_RENDERER
#include "dx9/DX9Renderer.h"
#elif OPENGL_RENDERER
#include "opengl/OpenGLRenderer.h"
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