#ifndef __ENGINE_CONFIG__
#define __ENGINE_CONFIG__
#include "renderer/RendererConfig.h"
#include "core/math/Vector3.h"
#include "external/jsoncpp-src-0.5.0/include/json/json.h"
#include <vector>
#include <map>
using namespace std;

class SceneData
{
public:

	SceneData()
	{

	}

	SceneData(std::string name, std::string filename)
	{
		this->name = name;
		this->filename = filename;
	}

	std::string name;
	std::string filename;
};

class EngineConfig
{

public:
	EngineConfig();
	~EngineConfig();

	static void LoadConfigFile();

	static RendererConfig::RENDER_API GetRendererAPI();

	static const char* ReadFileIntoString( const char* fileName );

	static char *WindowHandle;
	static RendererConfig renderConfig;
	static map<std::string, SceneData*> scenes;
	static SceneData *startScene;
	static Vector3 ClientAreaOrigin;
	static Vector3 ClientAreaWidthHeight;

private:

	static void LoadRenderSettings(Json::Value root, Json::Reader reader);
	static void LoadSceneSettings(Json::Value root, Json::Reader reader);

};

#endif
