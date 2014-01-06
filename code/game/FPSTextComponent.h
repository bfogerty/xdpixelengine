#ifndef __FPS_TEXT_COMPONENT__
#define __FPS_TEXT_COMPONENT__
#include "GameObjectComponent.h"
#include <string>

class Mesh;
class TextComponent;

class FPSTextComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		FPSTextComponent *component = new FPSTextComponent(pGameObject, mapParams );

		return (GameObjectComponent*)component;
	}

	FPSTextComponent( GameObject *pGameObject, std::map<std::string, std::string> mapParams ) : GameObjectComponent(pGameObject)
	{
		Intialize( mapParams );
	}

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	void Intialize( std::map<std::string, std::string> mapParams );

	TextComponent *textComponent;
};

#endif