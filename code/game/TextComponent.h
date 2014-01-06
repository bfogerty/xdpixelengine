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
		std::string characterWidth = mapParams["characterwidth"];
		std::string characterHeight = mapParams["characterheight"];
		std::string characterScale = mapParams["characterscale"];
		std::string characterKerning = mapParams["kerning"];
		std::string spaceBetweenCharacters = mapParams["spaceBetweenCharacters"];

		
		int cWidth = 0;
		int cHeight = 0;
		float cScale = 0.0f;
		float cKerning = 0.0f;
		float cSpace = 0.0f;

		sscanf(characterWidth.c_str(), "%d", &cWidth);
		sscanf(characterHeight.c_str(), "%d", &cHeight);
		sscanf(characterScale.c_str(), "%f", &cScale);
		sscanf(characterKerning.c_str(), "%f", &cKerning);
		sscanf(spaceBetweenCharacters.c_str(), "%f", &cSpace);


		TextComponent *component = new TextComponent(pGameObject, cWidth, cHeight, cSpace, cKerning, cSpace);
		
		component->SetText( text );

		return (GameObjectComponent*)component;
	}

	TextComponent( GameObject *pGameObject, int pixelWidthOfEachCharacter, int pixelHeightOfEachCharacter, float characterScale, float kerning, float spaceBetweenCharacters ) : GameObjectComponent(pGameObject), textMesh(0)
	{
		Intialize( pixelWidthOfEachCharacter, pixelHeightOfEachCharacter, characterScale, kerning, spaceBetweenCharacters );
	}

	void SetText( std::string text );

	virtual void OnAwake();
	virtual void OnUpdate();

protected:

	void Intialize( int pixelWidthOfEachCharacter, int pixelHeightOfEachCharacter, float characterScale, float kerning, float spaceBetweenCharacters );

	Mesh *textMesh;
	float pixelWidthPerCharacter;
	float pixelHeightPerCharacter;
	float characterScale;
	float kerning;
	float spaceBetweenCharacters;
	std::string textString;

};

#endif