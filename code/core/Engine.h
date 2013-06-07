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
	RenderEngine *pRenderEngine;

};