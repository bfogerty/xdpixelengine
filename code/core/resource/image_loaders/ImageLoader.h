#ifndef __IMAGE_LOADER__
#define __IMAGE_LOADER__

#include "../texture2d/Texture2D.h"

class ImageLoader
{
public:

	static Texture2D* Load(string strName );

	unsigned char *data;
	unsigned int iTextureID;
	unsigned int Width;
	unsigned int Height;

protected:
	virtual Texture2D* Load_Internal( string strName ){ return 0; };

};

#endif