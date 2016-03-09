#pragma once

#include "Pixel.h"

#include <string>
#include <functional>

#include <algorithm>



#define for_each_pixel(image) \
	for(int x = 0; x < image->width; x++) { \
	for(int y = 0; y < image->height; y++) { \
		Pixel* pixel = image->pixelAt(x, y);
#define for_each_pixel_end	delete pixel;}}

namespace npcv {

	typedef unsigned char uchar;




	class Image
	{
	public:
		Image();
		Image(Image* image);
		Image(int width, int height, PixelType type);
		Image(uchar* data, int width, int height, PixelType type);
		~Image();

		uchar* pixels;
		int width;
		int height;
		PixelType type;
		std::function<void(Image*)> freeDataFunc;

		Pixel* pixelAt(int x, int y);

		uchar* pixelAt_ptr(int x, int y);

		void pixelSet(int x, int y, int r, int g, int b);

		void pixelSet(int x, int y, Pixel* value);


		void pixelSet_ptr(int x, int y, uchar* colorPtr);

		bool loadFromMemory(unsigned char* fileMem, size_t bytes);

		Image* getSubImage(int x, int y, int width, int height);

		bool saveToFile(std::string filepath);

		bool convertToGrayscale();

		bool threshold(int borderValue);

		void foreachPixel(std::function<void(Pixel*)> iterFunction);

		bool setColor(int r, int g, int b);

		Image operator+(Image image) {
			Image ret = Image(width, height, type);
			for_each_pixel(this)
				Pixel* px2 = image.pixelAt(x, y);
				Pixel np = (*px2 + *pixel);
				ret.pixelSet(x, y, &np);
				delete px2;
				//int r = R(pixel);
				//int g = G(pixel);
				//int b = B(pixel);
				//r += R(px2);
				//g += G(px2);
				//b += B(px2);
				//r = std::max(std::min(r, 255), 0);
				//g = std::max(std::min(g, 255), 0);
				//b = std::max(std::min(b, 255), 0);
				//ret.pixelSet(x, y, r, g, b);
			for_each_pixel_end
			return ret;
		}

		void operator+=(Image image) {
			for_each_pixel(this)
				Pixel* px2 = image.pixelAt(x, y);
				*pixel += *px2;
				delete px2;
			for_each_pixel_end
		}

		void operator-=(Image image) {
			for_each_pixel(this)
				Pixel* px2 = image.pixelAt(x, y);
				*pixel -= *px2;
			for_each_pixel_end
		}

		Image operator-(Image image) {
			Image ret = Image(width, height, type);
			for_each_pixel(this)
				Pixel* px2 = image.pixelAt(x, y);
				ret.pixelSet(x, y, &(*pixel - *px2));
			for_each_pixel_end
			return ret;
		}



	};

}

