#include "npcv/types/Image.h"
#include <iostream>
#include <malloc.h>
#include <string.h>

#include "thirdparty/stb/stb_image.h"


namespace npcv {

	Image::Image()
	{
	}

	Image::Image(Image * image)
		: Image(image->pixels, image->width, image->height, image->type)
	{
	}

	Image::Image(int width, int height, PixelType type)
		: width(width), height(height), type(type)
	{
		size_t memSize = sizeof(unsigned char) * width * height * type;
		pixels = (uchar*)malloc(memSize);
		memset(pixels, 255, memSize);
	}

	Image::Image(uchar* data, int width, int height, PixelType type) 
		: pixels(data), width(width), height(height), type(type)
	{
	}

	Image::~Image()
	{
	}

	Pixel * Image::pixelAt(int x, int y)
	{
		return new Pixel(pixelAt_ptr(x, y), (PixelType)type);
	}

	uchar* Image::pixelAt_ptr(int x, int y)
	{
		uchar* pixel = 0;
		
		int pos = (x + y * width) * type;
		pixel = pixels + pos;
		return pixel;

		int columnPosition = x * type;
		int rowBeginPosition = width * type * y;
		uchar* rowBegin = pixels + rowBeginPosition;
		pixel = rowBegin + columnPosition;
		return pixel;
	}

	void Image::pixelSet(int x, int y, int r, int g, int b)
	{
		if (type < RGB) {
			std::cerr << "npcv: Image::pixelSet: missing RGB components" << std::endl;
			return;
		}
		uchar* pixel = pixelAt_ptr(x, y);
		*(pixel) = r;
		*(pixel + 1) = g;
		*(pixel + 2) = b;
	}

	void Image::pixelSet(int x, int y, Pixel * value)
	{
		pixelSet_ptr(x, y, value->firstComp);
	}

	void Image::pixelSet_ptr(int x, int y, uchar* firstComp)
	{
		uchar* pixel = pixelAt_ptr(x, y);
		for (int i = 0; i < type; i++) {
			*(pixel + i) = *(firstComp + i);
		}
	}

	bool Image::loadFromMemory(unsigned char * fileMem, size_t bytes)
	{
		int w, h, t;
		unsigned char* imageData = stbi_load_from_memory(fileMem, bytes, &w, &h, &t, 0);
		if (imageData != 0) {
			this->pixels = imageData;
			this->width = w;
			this->height = h;
			this->type = (PixelType)t;

			return true;
		}
		return false;
	}

	Image * Image::getSubImage(int x, int y, int width, int height)
	{
		Image * ret = 0;
		Pixel * pixelTemp = 0;
		uchar * newData = 0;

		int srcPos, srcColumnPosition, srcCowBeginPosition, srcOffset;
		int dstPos, dstColumnPosition, dstCowBeginPosition, dstOffset;

		uchar *ipx;

		if (x + width > this->width || y + height > this->height)
		{
			//bad params...
		}
		else
		{
			ret = new Image(width, height, this->type);

			srcColumnPosition = x * this->type;
			srcCowBeginPosition = this->width * this->type * y;
			srcPos = srcCowBeginPosition + srcColumnPosition;
			srcOffset = srcPos;

			dstColumnPosition = 0;
			dstCowBeginPosition = width * this->type * y;
			dstPos = dstCowBeginPosition + dstColumnPosition;
			dstOffset = dstPos;
			ipx = 0;

			for (int ix = x; ix < width + x; ix++)
			{
				for (int iy = y; iy < height + y; iy++)
				{
					srcColumnPosition = ix * this->type;
					srcCowBeginPosition = this->width * this->type * iy;
					srcOffset = srcCowBeginPosition + srcColumnPosition;

					ipx = this->pixels + srcOffset;

					dstColumnPosition = (ix - x) * this->type;
					dstCowBeginPosition = width * this->type * iy;
					dstPos = dstCowBeginPosition + dstColumnPosition;

					memcpy(ret->pixels + dstPos - dstOffset, ipx, sizeof(uchar) * this->type);
				}
			}

		}
		return ret;
	}

}