#include "TextComponent.h"
#include "../core/GameObject.h"
#include "../core/mesh/Mesh.h"
#include "../core/Transform.h"
#include "../core/time/Time.h"
#include "./resource/image_loaders/ImageLoader.h"

#include "../core/math/Vector3.h"
#include "../core/math/Quaternion.h"
#include "../core/math/MathHelper.h"

//-----------------------------------------------------------------------------------
void TextComponent::OnAwake()
{
	this->mpGameObject->pTexture = ImageLoader::Load("./assets/textures/ddrsmall.png");
	int pixelWidthOfEachCharacter = 9;
	pixelWidthPerCharacter = (float)(pixelWidthOfEachCharacter) / this->mpGameObject->pTexture->Width;
	pixelHeightPerCharacter = 9.00000f / this->mpGameObject->pTexture->Height;

	characterScale = 0.02f;
	kerning = 0.020f;
	spaceBetweenCharacters = 0.025f;
}

//-----------------------------------------------------------------------------------
void TextComponent::OnUpdate()
{
	
}

//-----------------------------------------------------------------------------------
void TextComponent::SetText(char *text)
{		
	int len = strlen(text);
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

		m->verticies.push_back( new Vector3( x,y,z   ) );
		m->verticies.push_back( new Vector3( x,y+characterScale,z ) );
		m->verticies.push_back( new Vector3( x+characterScale,y+characterScale,z ) );

		m->verticies.push_back( new Vector3( x+characterScale,y+characterScale,z ) );
		m->verticies.push_back( new Vector3( x+characterScale,y,z ) );
		m->verticies.push_back( new Vector3( x,y,z ) );
		
		

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