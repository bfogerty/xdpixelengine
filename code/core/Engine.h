#ifndef __ENGINE__
#define __ENGINE__

#include "RendererConfig.h"
#include "RenderEngine.h"

struct EngineConfig
{
	char *WindowHandle;
};

class Engine
{
public:
	Engine(EngineConfig config);

	void Update();

	~Engine();

	static unsigned int TotalFramesSinceStartup;

protected:

	void UpdateGameObject( GameObject *pGameObject );

	RenderEngine *pRenderEngine;
	GameObject *mpRootGameObject;

};

#endif