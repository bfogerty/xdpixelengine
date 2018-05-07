#ifndef __OPENGL_TEXTURE_2D__
#define __OPENGL_TEXTURE_2D__

#include "core/platform.h"
#include "core/resource/texture2d/Texture2D.h"
using namespace std;

class OpenGLTexture2D : public Texture2D
{

public:
	OpenGLTexture2D(unsigned char *data, 
					unsigned int width, 
					unsigned int height) : Texture2D(data,width,height), iTextureID(0)
	{

	}

	int iTextureID;
	
};
#endif