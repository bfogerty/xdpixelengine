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
		Texture2D(unsigned char *data, unsigned int width, unsigned int height);

		unsigned char *data;
		unsigned int Width;
		unsigned int Height;
};


#endif