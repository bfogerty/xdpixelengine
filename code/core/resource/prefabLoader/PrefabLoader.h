#ifndef __PREFAB_LOADER__
#define __PREFAB_LOADER__

#include <map>

class GameObject;
class GameObjectComponent;

class PrefabLoader
{
public:
	static GameObject* Load(const char* strFilename);
	static GameObject* Load(const char* strFilename, GameObject *pGo);


protected:
	static const char* ReadFileIntoString( const char* fileName );
	static GameObjectComponent *AddComponent( GameObject *pGameObject, std::map<std::string, std::string> mapParams );
};

#endif