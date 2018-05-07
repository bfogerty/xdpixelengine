#ifndef __SCENE_LOADER__
#define __SCENE_LOADER__

#include <map>

class GameObject;
class GameObjectComponent;

class SceneLoader
{
public:
	static void Load(const char* strFilename, GameObject *root);

protected:
	static const char* ReadFileIntoString( const char* fileName );

	static void CreateSceneObject( GameObject *parent, std::map<std::string, std::string> mapParams );
};

#endif