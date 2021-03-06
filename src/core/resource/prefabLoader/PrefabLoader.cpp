#include "core/GameObject.h"
#include "core/GameObjectComponent.h"
#include "core/resource/prefabLoader/PrefabLoader.h"
#include "graphics/Material.h"
#include "external/jsoncpp-src-0.5.0/include/json/json.h"
#include <string>
#include <fstream>
#include <map>
using namespace std;

GameObject *PrefabLoader::Load(const char* strFileName)
{
	return Load( strFileName, 0 );
}

GameObject *PrefabLoader::Load(const char* strFileName, GameObject *pGo)
{
	Json::Value root;
	Json::Reader reader;

	const char* jsonText = ReadFileIntoString( strFileName );

	if( !reader.parse( jsonText, root ) )
	{
		return 0;
	}

	if( pGo == 0 )
	{
		Json::Value nameVal = root["name"];
		std::string name = nameVal.asString();
		pGo = new GameObject( name.c_str() );
	}

	Json::Value componentsVal = root["components"];
	int componentCount = componentsVal.size();

	for( int i=0; i< componentCount; ++i )
	{
		Json::Value componentVal = componentsVal[i];
		Json::Value::Members members = componentVal.getMemberNames();
		
		std::map<std::string, std::string> mapParams;
		for( Json::Value::Members::iterator it = members.begin(); it != members.end(); ++it)
		{
			std::string memberName = *it;
			std::string value = componentVal[memberName].asString();

			mapParams[memberName] = value;
		}

		AddComponent( pGo, mapParams );
	}

	return pGo;
}

GameObjectComponent * PrefabLoader::AddComponent( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
{
	std::string name = mapParams["name"];

	GameObjectComponent *pComponent = GameObjectComponent::GetClass( name.c_str() )(pGameObject, mapParams);
	pGameObject->AddComponent( pComponent );

	return pComponent;
}

const char* PrefabLoader::ReadFileIntoString( const char* fileName )
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

