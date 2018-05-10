#ifndef __ENGINE__
#define __ENGINE__

#include "graphics/RendererConfig.h"
#include "graphics/RenderEngine.h"
#include "core/config/EngineConfig.h"


class Engine
{
public:
	Engine();

	void Update();

	~Engine();

	static unsigned int TotalFramesSinceStartup;

protected:

	void UpdateGameObject( GameObject *pGameObject );

	RenderEngine *pRenderEngine;
	GameObject *mpRootGameObject;
};

#endif