#ifndef __IMAGE_LOADER_PNG__
#define __IMAGE_LOADER_PNG__

#include "ImageLoader.h"
#include "../texture2d/Texture2D.h"

class ImageLoader_PNG : public ImageLoader
{
public:
	virtual Texture2D* Load_Internal( string strName );

protected:
	png_bytep *rowPtrs;

};

#endif