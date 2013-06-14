#ifndef __DX9_TEXTURE_2D__
#define __DX9_TEXTURE_2D__

#include "Texture2D.h"
#include "platform.h"
#include <d3d9.h>
using namespace std;

class DX9Texture2D : public Texture2D
{

public:
	DX9Texture2D(	unsigned char *data, 
					unsigned int width, 
					unsigned int height) : Texture2D(data, Width, Height), mpTexture(0)
	{

	}

	LPDIRECT3DTEXTURE9 mpTexture;

};

#endif



