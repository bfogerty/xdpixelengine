#include "game/TextComponent.h"
#include "core/GameObject.h"
#include "core/mesh/Mesh.h"
#include "core/Transform.h"
#include "core/time/Time.h"
#include "core/resource/materialLoader/MaterialLoader.h"

#include "core/math/Vector3.h"
#include "core/math/Quaternion.h"
#include "core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void TextComponent::Intialize( int pixelWidthOfEachCharacter, int pixelHeightOfEachCharacter, float characterScale, float kerning, float spaceBetweenCharacters )
{
	Texture2D *tex = mpGameObject->pMaterial->GetMainTextureEntry();
	pixelWidthPerCharacter = (float)(pixelWidthOfEachCharacter) / tex->Width;
	pixelHeightPerCharacter = pixelHeightOfEachCharacter / (float)(tex->Height);

	this->characterScale = characterScale;
	this->kerning = kerning;
	this->spaceBetweenCharacters = spaceBetweenCharacters;
}

//-----------------------------------------------------------------------------------
void TextComponent::OnAwake()
{

}

//-----------------------------------------------------------------------------------
void TextComponent::OnUpdate()
{
	
}

//-----------------------------------------------------------------------------------
void TextComponent::SetText(std::string textstring)
{
	if( this->textString == textstring )
	{
		return;
	}

	this->textString = textstring;
	const char *text = this->textString.c_str();
	int len = textString.length();
	Mesh *m = new Mesh();

	float x = 0;
	float y = 0;
	float z = 0;

	int mi = 0;
	for(int i=0; i<len; ++i)
	{
		
		if( text[i] == ' ' )
		{
			x += spaceBetweenCharacters;
			continue;
		}

		float to = (text[i] - '!') * pixelWidthPerCharacter;

		m->verticies.push_back(Vector3( x,y,z   ) );
		m->verticies.push_back(Vector3( x,y+characterScale,z ) );
		m->verticies.push_back(Vector3( x+characterScale,y+characterScale,z ) );

		m->verticies.push_back(Vector3( x+characterScale,y+characterScale,z ) );
		m->verticies.push_back(Vector3( x+characterScale,y,z ) );
		m->verticies.push_back(Vector3( x,y,z ) );
		
		

		m->uvs.push_back( new Vector3( to,     0,     0   ) );
		m->uvs.push_back( new Vector3( to,     pixelHeightPerCharacter,     0   ) );
		m->uvs.push_back( new Vector3( to+pixelWidthPerCharacter,     pixelHeightPerCharacter,     0   ) );

		m->uvs.push_back( new Vector3( to+pixelWidthPerCharacter,     pixelHeightPerCharacter,     0   ) );
		m->uvs.push_back( new Vector3( to+pixelWidthPerCharacter,     0,     0   ) );
		m->uvs.push_back( new Vector3( to,     0,     0   ) );

		m->normals.push_back( new Vector3(0,0,1.00f) );
		m->colors.push_back( new Color( Color::WHITE ) );

		m->triangles.push_back( new Face( (mi * 6) + 0, mi, mi,	(mi * 6) + 0  ));
		m->triangles.push_back( new Face( (mi * 6) + 1, mi, mi,	(mi * 6) + 1  ));
		m->triangles.push_back( new Face( (mi * 6) + 2, mi, mi,	(mi * 6) + 2  ));
		m->triangles.push_back( new Face( (mi * 6) + 3, mi, mi,	(mi * 6) + 3  ));
		m->triangles.push_back( new Face( (mi * 6) + 4, mi, mi,	(mi * 6) + 4  ));
		m->triangles.push_back( new Face( (mi * 6) + 5, mi, mi,	(mi * 6) + 5  ));

		x += kerning;
		++mi;
	}

	m->Build();

	this->mpGameObject->mMesh->Clone( m );

}