#include "ImageLoader.h"
#include "ImageLoader_PNG.h"

Texture2D* ImageLoader::Load( string strName )
{
	ImageLoader_PNG *pLoader = new ImageLoader_PNG();
	Texture2D *pTex = pLoader->Load_Internal(strName);

	return pTex;
}