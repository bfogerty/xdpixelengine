#ifndef __TEXTURE_2D__
#define __TEXTURE_2D__

#include "core/platform.h"
#include "external/lpng162/png.h"
#include <string>
#include <iostream>


#ifdef COMPILE_OPENGL_RENDERER
#include "windows.h"
#include "external/glad/glad.h"
#endif

using namespace std;

class Texture2D
{
public:
		Texture2D(unsigned char *data, unsigned int width, unsigned int height);

		unsigned char *data;
		unsigned int Width;
		unsigned int Height;
};


#endif