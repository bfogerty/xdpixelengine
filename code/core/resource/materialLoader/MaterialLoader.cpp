#include "MaterialLoader.h"
#include "GameObject.h"
#include "GameObjectComponent.h"
#include "../renderer/Material.h"
#include "../core/resource/image_loaders/ImageLoader.h"
#include <string>
#include "json/json.h"
#include <fstream>
#include <map>
using namespace std;

Material *MaterialLoader::Load(const char* strFileName)
{
	Material *mat = 0;
	Json::Value root;
	Json::Reader reader;

	const char* jsonText = ReadFileIntoString( strFileName );

	if( !reader.parse( jsonText, root ) )
	{
		return 0;
	}

	Json::Value nameVal = root["name"];
	std::string name = nameVal.asString();
	mat = new Material( name.c_str() );

	Json::Value shaderVal = root["shader"];
	std::string shader = shaderVal.asString();
	mat->SetShaderProgram(shader.c_str());

	Json::Value componentsVal = root["parameters"];
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

		SetShaderParam( mat, mapParams );
	}

	return mat;
}

void MaterialLoader::SetShaderParam( Material* mat, std::map<std::string, std::string> mapParams )
{
	std::string typeVal = mapParams["type"];
	std::string nameVal = mapParams["name"];
	std::string valString = mapParams["value"];

	if( typeVal == "texture2d" )
	{
		std::string texturePath = valString;
		Texture2D* tex2d = ImageLoader::Load( texturePath );
		mat->AddTextureEntry( nameVal, tex2d );
	}
	else if( typeVal == "float" )
	{
		float floatVal = 0.0f;
		sscanf( valString.c_str(), "%f", &floatVal );
		mat->SetFloat( nameVal.c_str(), floatVal );
	}
	else if( typeVal == "color" )
	{
		float r,g,b;
		sscanf( valString.c_str(), "%f,%f,%f", &r, &g, &b );
		mat->SetVector3( nameVal.c_str(), Vector3(r,g,b) );
	}
	else if( typeVal == "vector3" )
	{
		float x,y,z;
		sscanf( valString.c_str(), "%f,%f,%f", &x, &y, &z );
		mat->SetVector3( nameVal.c_str(), Vector3(x,y,z) );
	}
}

const char* MaterialLoader::ReadFileIntoString( const char* fileName )
{
	char *buffer = 0;
	fstream f;
	f.open( fileName );
	f.seekg(0, std::ios::end);
	int len = f.tellg();
	buffer = new char[len];
	f.seekg(0, std::ios::beg);
	f.read(buffer,len);
	f.close();

	return buffer;
}

