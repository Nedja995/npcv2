#include "npcv/types/Image.h"
#include <iostream>
#include <malloc.h>
#include <string.h>

#include "thirdparty/stb/stb_image.h"
#include "npcv/Toolset.h"

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
			uchar* pixel = pixelAt_ptr(x, y);
			*(pixel) = r;
		}
		else if (type >= RGB) {
			uchar* pixel = pixelAt_ptr(x, y);
			*(pixel) = r;
			*(pixel + 1) = g;
			*(pixel + 2) = b;
		}

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

	bool Image::saveToFile(std::string filepath)
	{	
		return Toolset::SharedInstance()->imageStream->Save(this, filepath);
	}
	static int vp = 0;
	bool Image::convertToGrayscale()
	{
		if (type == GRAY) { return false; }
		Image* gray = new Image(width, height, PixelType::GRAY);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Pixel* px = pixelAt(x, y);
				int val = R(px) + G(px) + B(px);
				val /= 3;
				if (val == 205) {
					int a = 3;
				}
				if (R(px) != vp) {
					vp = R(px);
				}
				R(gray->pixelAt(x, y)) = val;

			}
		}
		free(pixels);
		pixels = gray->pixels;

		type = GRAY;
		return true;
	}

	bool Image::threshold(int borderValue)
	{
		Image::convertToGrayscale();
		Image* tresh = new Image(width, height, type);

		for (int x = 0; x < width; x++) {
			for (int y = 0; y < height; y++) {
				Pixel* px = pixelAt(x, y);
				int val = R(px);
				if (val < borderValue) {
					R(tresh->pixelAt(x, y)) = 0;
				}
				else {
					R(tresh->pixelAt(x, y)) = 255;
				}
			}
		}
		free(pixels);
		pixels = tresh->pixels;
		return true;
	}

	void Image::foreachPixel(std::function<void(Pixel*)> iterFunction)
	{
		for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			iterFunction(pixelAt(x, y));
		}
		}
	}

	bool Image::setColor(int r, int g, int b)
	{
		for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Pixel* p = pixelAt(x, y);
			if (type == RGB) {
				R(p) = r;
				G(p) = g;
				B(p) = b;
			}
			else if (type == GRAY) {
				R(p) = r;
			}
			else {
				return false;
			}
		}
		}
		return true;
	}

}