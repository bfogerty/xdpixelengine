#include "PlatformRenderer.h"

//#ifdef DX9_RENDERER
#include "dx9/DX9Renderer.h"
//#endif

#include "opengl/OpenGLRenderer.h"

class GameObject;

class RenderEngine
{
public:

	RenderEngine( RendererConfig config );
	~RenderEngine();

	void Render(GameObject *pGameObject);

protected:
	PlatformRenderer *mRenderer;
};