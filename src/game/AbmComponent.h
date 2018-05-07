#ifndef __ABM_COMPONENT__
#define __ABM_COMPONENT__
#include "core/GameObjectComponent.h"

#include "core/math/Matrix4x4.h"
#include <map>

class AbmData;
class AbmClipData;

class TextComponent;

class AbmComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string model = mapParams["model"];

		return (GameObjectComponent*)new AbmComponent(pGameObject, model);
	}

	AbmComponent( GameObject *pGameObject, std::string modelPath ) : GameObjectComponent(pGameObject)
	{
		this->modelPath = modelPath;
	}

	virtual void OnAwake();
	virtual void OnUpdate();

	void PlayClip(string clipName);
	void PlayClip( int clipIndex );

	void DrawAABB();

protected:

	std::string modelPath;
	AbmData *abmData;
	AbmClipData *currentClip;
	int currentClipIndex;
	int currentFrameIndex;
	float tVal;
	bool paused;
	bool showNormals;
	
	TextComponent *textComponent;
};

#endif