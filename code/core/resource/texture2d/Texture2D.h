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

#include "../renderer/RenderEngine.h"
#include "../renderer/PlatformRenderer.h"

using namespace std;

class Texture2D
{

public:
		Texture2D(unsigned char *data, unsigned int width, unsigned int height);

		TextureInfo* GetTextureMemoryData() { return mpTextureInfo; }
		unsigned char *data;
		unsigned int Width;
		unsigned int Height;

protected:
		TextureInfo *mpTextureInfo;
};


#endif