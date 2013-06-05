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

protected:
	RenderEngine *pRenderEngine;

};