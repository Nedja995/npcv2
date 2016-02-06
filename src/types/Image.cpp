#include "npcv/types/Image.h"
#include <iostream>
#include <malloc.h>
#include <string.h>
namespace npcv {


	Image::Image()
	{
	}

	Image::Image(int width, int height, PixelType type)
		: width(width), height(height), type(type)
	{
		size_t memSize = sizeof(unsigned char) * width * height * type;
		pixels = (unsigned char*)malloc(memSize);
		memset(pixels, 255, memSize);
	}

	Image::Image(unsigned char * data, int width, int height, PixelType type) 
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

	unsigned char * Image::pixelAt_ptr(int x, int y)
	{
		unsigned char * pixel = nullptr;
		int columnPosition = x * type;
		int rowBeginPosition = width * type * y;
		unsigned char* rowBegin = pixels + rowBeginPosition;
		pixel = rowBegin + columnPosition;
		return pixel;
	}

	void Image::pixelSet(int x, int y, int r, int g, int b)
	{
		if (type < RGB) {
			std::cerr << "npcv: Image::pixelSet: missing RGB components" << std::endl;
			return;
		}
		unsigned char* pixel = pixelAt_ptr(x, y);
		*(pixel) = r;
		*(pixel + 1) = g;
		*(pixel + 2) = b;
	}

	void Image::pixelSet(int x, int y, Pixel * value)
	{
		pixelSet_ptr(x, y, value->firstComp);
	}

	void Image::pixelSet_ptr(int x, int y, unsigned char * firstComp)
	{
		unsigned char* pixel = pixelAt_ptr(x, y);
		for (int i = 0; i < type; i++) {
			*(pixel + i) = *(firstComp + i);
		}
	}

	Image * Image::getSubImage(int x, int y, int width, int height)
	{
		return nullptr;
	}

}