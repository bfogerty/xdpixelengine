#ifndef __TEXT_COMPONENT__
#define __TEXT_COMPONENT__
#include "GameObjectComponent.h"

class Mesh;

class TextComponent : public GameObjectComponent
{
public:

	TextComponent( GameObject *pGameObject ) : GameObjectComponent(pGameObject), textMesh(0)
	{

	}

	void SetText( char *text );

	virtual void OnAwake();
	virtual void OnUpdate();

protected:
	Mesh *textMesh;
	float pixelWidthPerCharacter;
	float pixelHeightPerCharacter;
	float characterScale;
	float kerning;
	float spaceBetweenCharacters;

};

#endif