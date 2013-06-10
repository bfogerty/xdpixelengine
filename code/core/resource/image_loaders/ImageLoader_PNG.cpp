#include "ImageLoader_PNG.h"
#include <fstream>
#include <string>
#include <iostream>
#include "lpng162/png.h"

#define PNGSIGSIZE 8 

void userReadData(png_structp pngPtr, png_bytep data, png_size_t length) {
	//Here we get our IO pointer back from the read struct.
	//This is the parameter we passed to the png_set_read_fn() function.
	//Our std::istream pointer.
	png_voidp a = png_get_io_ptr(pngPtr);
	//Cast the pointer to std::istream* and read 'length' bytes into 'data'
	((std::istream*)a)->read((char*)data, length);
}

Texture2D* ImageLoader_PNG::Load_Internal( string strName )
{
	ifstream file;
	file.open(strName.c_str(), ios_base::binary);

	png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	png_infop infoPtr = png_create_info_struct(pngPtr);
	png_set_read_fn(pngPtr,(png_voidp)&file, userReadData);

	png_read_info(pngPtr, infoPtr);

	png_uint_32 imgWidth =  png_get_image_width(pngPtr, infoPtr);
	png_uint_32 imgHeight = png_get_image_height(pngPtr, infoPtr);

	Width = imgWidth;
	Height = imgHeight;

	//bits per CHANNEL! note: not per pixel!
	png_uint_32 bitdepth   = png_get_bit_depth(pngPtr, infoPtr);
	//Number of channels
	png_uint_32 channels   = png_get_channels(pngPtr, infoPtr);
	//Color type. (RGB, RGBA, Luminance, luminance alpha... palette... etc)
	png_uint_32 color_type = png_get_color_type(pngPtr, infoPtr);

	switch (color_type) {
		case PNG_COLOR_TYPE_PALETTE:
			png_set_palette_to_rgb(pngPtr);
			//Don't forget to update the channel info (thanks Tom!)
			//It's used later to know how big a buffer we need for the image
			channels = 3;           
			break;
		case PNG_COLOR_TYPE_GRAY:
			if (bitdepth < 8)
				png_set_expand_gray_1_2_4_to_8(pngPtr);
			//And the bitdepth info
			bitdepth = 8;
			break;
	}

	/* if the image has a transparency set.. convert it to a full Alpha channel..*/
	if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS)) {
		png_set_tRNS_to_alpha(pngPtr);
		channels+=1;
	}

	//We don't support 16 bit precision.. so if the image Has 16 bits per channel
	//precision... round it down to 8.
	if (bitdepth == 16)
		png_set_strip_16(pngPtr);

	//Here's one of the pointers we've defined in the error handler section:
	//Array of row pointers. One for every row.
	rowPtrs = new png_bytep[imgHeight];

	//Allocate a buffer with enough space.
	//(Don't use the stack, these blocks get big easily)
	//This pointer was also defined in the error handling section, so we can clean it up on error.
	data = new unsigned char[imgWidth * imgHeight * bitdepth * channels / 8];
	//This is the length in bytes, of one row.
	const unsigned int stride = imgWidth * bitdepth * channels / 8;

	//A little for-loop here to set all the row pointers to the starting
	//Addresses for every row in the buffer

	for (size_t i = 0; i < imgHeight; i++) {
		//Set the pointer to the data pointer + i times the row stride.
		//Notice that the row order is reversed with q.
		//This is how at least OpenGL expects it,
		//and how many other image loaders present the data.
		png_uint_32 q = (imgHeight- i - 1) * stride;
		rowPtrs[i] = (png_bytep)data + q;
	}

	//And here it is! The actual reading of the image!
	//Read the imagedata and write it to the addresses pointed to
	//by rowptrs (in other words: our image data buffer)
	png_read_image(pngPtr, rowPtrs);

	file.close();

	Texture2D *pTexture = new Texture2D(data,Width,Height);

	return pTexture;
}