#include "core/resource/sceneLoader/SceneLoader.h"
#include "core/resource/prefabLoader/PrefabLoader.h"
#include "core/Transform.h"
#include "core/GameObject.h"
#include "core/GameObjectComponent.h"
#include "external/jsoncpp-src-0.5.0/include/json/json.h"
#include <string>
#include <fstream>
#include <map>
using namespace std;

void SceneLoader::Load(const char* strFileName, GameObject *rootGameObject)
{
	GameObject *pGo = 0;
	Json::Value root;
	Json::Reader reader;

	const char* jsonText = ReadFileIntoString( strFileName );

	if( !reader.parse( jsonText, root ) )
	{
		return;
	}


	Json::Value componentsVal = root["objects"];
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

		CreateSceneObject( rootGameObject, mapParams );
	}
}

void SceneLoader::CreateSceneObject( GameObject *parent, std::map<std::string, std::string> mapParams )
{
	std::string name = mapParams["name"];
	std::string prefab = mapParams["prefab"];
	std::string localPosition = mapParams["localPosition"];
	std::string localRotation = mapParams["localRotation"];
	std::string localScale = mapParams["localScale"];
	std::string layerStr = mapParams["layer"];

	float fX=0.0f;
	float fY=0.0f;
	float fZ=0.0f;
	unsigned int layer = 0;

	const char *locationPositionBuffer = localPosition.c_str();
	sscanf(locationPositionBuffer, "%f,%f,%f", &fX, &fY, &fZ);
	Vector3 vecPosition(fX, fY, fZ);

	const char *locationRotationBuffer = localRotation.c_str();
	sscanf(locationRotationBuffer, "%f,%f,%f", &fX, &fY, &fZ);
	Vector3 vecRotation(fX, fY, fZ);

	const char *locationScaleBuffer = localScale.c_str();
	sscanf(locationScaleBuffer, "%f,%f,%f", &fX, &fY, &fZ);
	Vector3 vecScale(fX, fY, fZ);

	const char *layerBuffer = layerStr.c_str();
	sscanf(layerBuffer, "%d", &layer);

	GameObject *pChild = new GameObject(name.c_str());
	if( prefab.length() > 0 )
	{
		PrefabLoader::Load( prefab.c_str(), pChild);
	}

	parent->mpTransform->mChildren.push_back(pChild->mpTransform);
	pChild->mpTransform->scale = vecScale;
	pChild->mpTransform->position = vecPosition;
	pChild->mpTransform->rotation = Quaternion::FromEulerAngles( vecRotation );
	pChild->mpTransform->Update();
	pChild->SetLayer( layer );
}

const char* SceneLoader::ReadFileIntoString( const char* fileName )
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

