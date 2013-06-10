#include "Texture2D.h"
#include <fstream>

Texture2D::Texture2D(unsigned char *data, unsigned int width, unsigned int height)
{
	this->data = data;
	this->Width = width;
	this->Height = height;

	Upload();
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

void Texture2D::Upload()
{

#ifdef COMPILE_OPENGL_RENDERER
	Upload_OpenGL();
#endif

}

#ifdef COMPILE_OPENGL_RENDERER
void Texture2D::Upload_OpenGL()
{
	int wrap = 1;
	glGenTextures(1, &iTextureID);
	glBindTexture(GL_TEXTURE_2D, iTextureID);

	/*
	// select modulate to mix texture with color for shading
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
		GL_LINEAR_MIPMAP_NEAREST );
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	// if wrap is true, the texture wraps over at the edges (repeat)
	//       ... false, the texture ends at the edges (clamp)
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S,
		wrap ? GL_REPEAT : GL_CLAMP );
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,
		wrap ? GL_REPEAT : GL_CLAMP );
	*/

	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, (GLvoid *)data);

	//// build our texture mipmaps
	gluBuild2DMipmaps( GL_TEXTURE_2D, 3, Width, Height,
		GL_RGB, GL_UNSIGNED_BYTE, data );
	
}
#endif

/*
bool Texture2D::Validate(std::istream &source)
{
	png_byte pngsig[PNGSIGSIZE];
	int isPNG = 0;

	source.read((char*)pngsig, PNGSIGSIZE);

	isPNG = png_sig_cmp(pngsig,0,PNGSIGSIZE);

	return (isPNG == 0);
}
*/