#include "Texture2D.h"
#include <fstream>

Texture2D::Texture2D(unsigned char *data, unsigned int width, unsigned int height)
{
	this->data = data;
	this->Width = width;
	this->Height = height;

	mpTextureInfo = RenderEngine::GetInstance()->GetRenderer()->CreateTexture(	this->data, 
																				this->Width, 
																				this->Height);
	
}

//void Texture2D::Load(string strName)
//{	
//		/*
//		int width, height;
//		//BYTE * data;
//		FILE * file;
//
//		// open texture data
//		file = fopen( "./assets/textures/texture.raw", "rb" );
//		if ( file == NULL ) return;
//
//		// allocate buffer
//		width = 256;
//		height = 256;
//		data = (unsigned char *)malloc( width * height * 3 );
//
//		// read texture data
//		fread( data, width * height * 3, 1, file );
//		fclose( file );
//
//		Width = width;
//		Height = height;
//		*/
//
//	Upload();
//}



