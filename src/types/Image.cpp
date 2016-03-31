#include "npcv/types/Image.h"
#include <iostream>
#include <malloc.h>
#include <string.h>

#include "thirdparty/stb/stb_image.h"
#include "npcv/Toolset.h"

namespace npcv {
	Image& Image::Create()
	{
		Image& ret = *new Image();
		return ret;
	}

	Image & Image::Create(int width, int height, PixelType type)
	{
		Image& ret = *new Image();
		ret.width = width;
		ret.height = height;
		ret.type = type;
		ret.pixels = new uchar[ret.memSize()]{ 0 };
		return ret;
	}

	Image & Image::Create(int width, int height, PixelType type, uchar * pixels)
	{
		Image& ret = Create(width, height, type);
		ret.pixels = pixels;
		return ret;
	}

	Image & Image::Create(Image & image)
	{
		Image& ret = Create(image.width, image.height, image.type, image.pixels);
		return ret;
	}

	Image& Image::Null()
	{
		Image& ret = *new Image();
		return ret;
	}

	Image::Image()
		: type(PixelType::Null)
		, pixels(nullptr)
	{
	}

	Image::Image(Image&  image)
		: Image(image.pixels, image.width, image.height, image.type)
	{
	}

	Image::Image(int width, int height, PixelType type)
		: width(width), height(height), type(type)
	{
		size_t memSize = sizeof(unsigned char) * width * height * type;
		pixels = new uchar[memSize];

		/*freeDataFunc = [](Image* image) {
			delete image->pixels;
		};*/
		memset(pixels, 255, memSize);
	}

	Image::Image(uchar* data, int width, int height, PixelType type) 
		: pixels(data), width(width), height(height), type(type)
	{
	}

	Image::~Image()
	{
		/*if (freeDataFunc != 0) {
			freeDataFunc(this);
		}*/
	}

	inline size_t Image::memSize()
	{
		return width * height * type * sizeof(uchar);
	}

	Pixel& Image::pixel(int x, int y)
	{
		return *new Pixel(pixel_ptr(x, y), (PixelType)type);
	}

	uchar* Image::pixel_ptr(int x, int y)
	{
		uchar* pixel = 0;
		
		int pos = (x + y * width) * type;
		pixel = pixels + pos;
		return pixel;

		//old
		int columnPosition = x * type;
		int rowBeginPosition = width * type * y;
		uchar* rowBegin = pixels + rowBeginPosition;
		pixel = rowBegin + columnPosition;
		return pixel;
	}

	//void Image::pixelSet(int x, int y, Pixel * value)
	//{
	//	pixelSet_ptr(x, y, value->colorPtr);
	//}

	void Image::pixelSet_ptr(int x, int y, uchar* colorPtr)
	{
		uchar* pixel = pixel_ptr(x, y);
		for (int i = 0; i < type; i++) {
			*(pixel + i) = *(colorPtr + i);
		}
	}

	bool Image::loadFromMemory(unsigned char * fileMem, size_t size)
	{
		int w, h, t;
		unsigned char* imageData = stbi_load_from_memory(fileMem, size, &w, &h, &t, 0);
		if (imageData != 0) {
			this->pixels = imageData;
			this->width = w;
			this->height = h;
			this->type = (PixelType)t;

			return true;
		}
		return false;
	}

	bool Image::setPixelsCopy(Image& image)
	{
		int re = memcpy_s(pixels, memSize(), image.pixels, image.memSize());
		if (re == 0) {
			true;
		}
		else {
			false;
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
		return Toolset::SharedInstance().imageStream.Save(*this, filepath);
	}

	bool Image::convertToGrayscale()
	{
		if (type == GRAY) { return false; }

		Image gray = Image(width, height, PixelType::GRAY);

		for_each_pixel((*this))
			gray.pixel(x, y)
				.setColor((pixel.color(0) + pixel.color(1) + pixel.color(2)) / 3);		
		for_each_pixel_end

		//free old and replace with new
		setPixelsCopy(gray);

		//change type
		type = GRAY;
		return true;
	}

	void Image::foreachPixel(std::function<void(Pixel&)> iterFunction)
	{
		for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			iterFunction(pixel(x, y));
		}
		}
	}

	bool Image::setColor(int r, int g, int b)
	{
		for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			Pixel& p = pixel(x, y);
			if (type == RGB) {
				p.setColor(r, g, b);
			}
			else if (type == GRAY) {
				p.setColor(r);
			}
			else {
				return false;
			}
		}
		}
		return true;
	}

}