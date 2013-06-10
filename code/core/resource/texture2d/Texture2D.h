#ifndef __TEXTURE_2D__
#define __TEXTURE_2D__

#include "platform.h"

#include <string>
#include <iostream>
#include "lpng162/png.h"

#ifdef COMPILE_OPENGL_RENDERER
#include "windows.h"
#include <gl/gl.h>
#include <gl/GLU.h>
#endif

using namespace std;

class Texture2D
{

public:

		Texture2D(){};
		
		void Load(string strName);
		
		void Upload();

#ifdef COMPILE_OPENGL_RENDERER
		void Upload_OpenGL();
#endif

		bool Validate(std::istream &source);


		//void userReadData(png_structp pngPtr, png_bytep data, png_size_t length);

		png_bytep *rowPtrs;
		unsigned char *data;
		unsigned int iTextureID;
		unsigned int Width;
		unsigned int Height;


};


#endif