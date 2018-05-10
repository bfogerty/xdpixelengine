#include "core/config/EngineConfig.h"
#include "graphics/RendererConfig.h"
#include "external/jsoncpp-src-0.5.0/include/json/json.h"
#include <string>
#include <fstream>
#include <map>

char *EngineConfig::WindowHandle;
RendererConfig  EngineConfig::renderConfig;

map<std::string, SceneData*> EngineConfig::scenes;
SceneData* EngineConfig::startScene;

Vector3 EngineConfig::ClientAreaOrigin;
Vector3 EngineConfig::ClientAreaWidthHeight;

//-----------------------------------------------------------------------------------
EngineConfig::EngineConfig()
{

}

//-----------------------------------------------------------------------------------
EngineConfig::~EngineConfig()
{

}

//-----------------------------------------------------------------------------------
void EngineConfig::LoadConfigFile()
{
	const char* filepath = "config.txt";
	const char* jsonText = ReadFileIntoString( filepath );

	Json::Value root;
	Json::Reader reader;

	if( !reader.parse( jsonText, root ) )
	{
		return;
	}

	LoadRenderSettings(root, reader);
	LoadSceneSettings(root, reader);
}

//-----------------------------------------------------------------------------------
void EngineConfig::LoadRenderSettings(Json::Value root, Json::Reader reader)
{
	Json::Value rendererSettings = root["renderer"];
	int componentCount = rendererSettings.size();

	for( int i=0; i< componentCount; ++i )
	{
		Json::Value componentVal = rendererSettings[i];
		Json::Value::Members members = componentVal.getMemberNames();

		for( Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			std::string memberName = *it;
			std::string value = componentVal[memberName].asString();

			if( memberName == "api" )
			{
				if( value == "dx9" )
				{
					EngineConfig::renderConfig.RenderAPI = RendererConfig::DX9;
				}
				else if( value == "opengl" )
				{
					EngineConfig::renderConfig.RenderAPI = RendererConfig::OPENGL;
				}
			}
			else if( memberName == "screenwidth" )
			{
				sscanf_s(value.c_str(), "%d", &EngineConfig::renderConfig.ScreenWidth);
			}
			else if( memberName == "screenheight" )
			{
				sscanf_s(value.c_str(), "%d", &EngineConfig::renderConfig.ScreenHeight);
			}
			else if( memberName == "fullscreen" )
			{
				int bfullScreen = 0;
				sscanf_s(value.c_str(), "%d", &bfullScreen);

				EngineConfig::renderConfig.FullScreen = (bool) bfullScreen;
			}
		}
	}
}

//-----------------------------------------------------------------------------------
void EngineConfig::LoadSceneSettings(Json::Value root, Json::Reader reader)
{
	Json::Value settings = root["scenes"];
	int componentCount = settings.size();

	for( int i=0; i< componentCount; ++i )
	{
		Json::Value componentVal = settings[i];
		Json::Value::Members members = componentVal.getMemberNames();

		map<std::string, std::string> mapValues;
		for( Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			std::string memberName = *it;
			std::string value = componentVal[memberName].asString();
			
			mapValues[memberName] = value;

		}

		std::string sceneName = mapValues["name"];
		std::string fileName = mapValues["file"];

		SceneData *sceneData = new SceneData( sceneName, fileName );

		scenes[sceneName] = sceneData;
	}

	settings = root["startscene"];
	startScene = scenes[settings.asCString()];
}

//-----------------------------------------------------------------------------------
RendererConfig::RENDER_API EngineConfig::GetRendererAPI()
{
	return renderConfig.RenderAPI;
}

const char* EngineConfig::ReadFileIntoString( const char* fileName )
{
	char *buffer = 0;
	fstream f;
	f.open( fileName );
	f.seekg(0, std::ios::end);
	std::streamoff len = f.tellg();
	buffer = new char[(unsigned int)len];
	f.seekg(0, std::ios::beg);
	f.read(buffer,len);
	f.close();

	return buffer;
}