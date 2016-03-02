#pragma once

#include "Pixel.h"

#include <string>
#include <functional>

#define R(pixel) *(pixel->firstComp )
#define G(pixel) *(pixel->firstComp + 1)
#define B(pixel) *(pixel->firstComp + 2)

#define for_each_pixel(image) \
	for(int x = 0; x < image->width; x++) { \
	for(int y = 0; y < image->height; y++) { \
		Pixel* pixel = image->pixelAt(x, y);
#define for_each_pixel_end	}}

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

		Pixel* pixelAt(int x, int y);

		uchar* pixelAt_ptr(int x, int y);

		void pixelSet(int x, int y, int r, int g, int b);

		void pixelSet(int x, int y, Pixel* value);


		void pixelSet_ptr(int x, int y, uchar* firstComp);

		bool loadFromMemory(unsigned char* fileMem, size_t bytes);

		Image* getSubImage(int x, int y, int width, int height);

		bool saveToFile(std::string filepath);

		bool convertToGrayscale();

		bool threshold(int borderValue);

		void foreachPixel(std::function<void(Pixel*)> iterFunction);

		bool setColor(int r, int g, int b);

		void operator+=(Image image) {
			//Image ret = Image(width, height, type);
			for_each_pixel(this)
				Pixel* px2 = image.pixelAt(x, y);
				int r = R(pixel);
				if (R(pixel) == 255) {
					int a = 2;
				}
				r -= R(px2);
				r = (r > 255) ? 255 : r;
				r = (r < 0) ? 0 : r;

				int g = G(pixel);
				g -= G(px2);
				g = (g > 255) ? 255 : g;
				g = (g < 0) ? 0 : g;

				int b = B(pixel);
				b -= B(px2);
				b = (b > 255) ? 255 : b;
				b = (b < 0) ? 0 : b;
				R(pixel) = r;
				G(pixel) = g;
				B(pixel) = b;
				//R(pixel) = R(pixel) - R(px2);
				//G(pixel) = G(pixel) - G(px2);
				//B(pixel) = B(pixel) - B(px2);
			for_each_pixel_end
			//return *this;
		}

	};

}

