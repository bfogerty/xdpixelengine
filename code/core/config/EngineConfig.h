#ifndef __ENGINE_CONFIG__
#define __ENGINE_CONFIG__
#include <vector>
#include <map>
#include "RendererConfig.h"
#include "json/json.h"
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

private:

	static void LoadRenderSettings(Json::Value root, Json::Reader reader);
	static void LoadSceneSettings(Json::Value root, Json::Reader reader);

};

#endif
