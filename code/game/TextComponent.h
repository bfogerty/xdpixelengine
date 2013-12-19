#ifndef __TEXT_COMPONENT__
#define __TEXT_COMPONENT__
#include "GameObjectComponent.h"
#include <string>

class Mesh;

class TextComponent : public GameObjectComponent
{
public:

	static GameObjectComponent* Create( GameObject *pGameObject, std::map<std::string, std::string> mapParams )
	{
		std::string text = mapParams["text"];
		TextComponent *component = new TextComponent(pGameObject);
		
		component->SetText( text );

		return (GameObjectComponent*)component;
	}

	TextComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject), textMesh(0)
	{
		Intialize();
	}

	void SetText( std::string text );

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	void Intialize();

	Mesh *textMesh;
	float pixelWidthPerCharacter;
	float pixelHeightPerCharacter;
	float characterScale;
	float kerning;
	float spaceBetweenCharacters;
	std::string textString;

};

#endif