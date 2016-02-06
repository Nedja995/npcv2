#pragma once

#define R(pixel) *(pixel->firstComp )
#define G(pixel) *(pixel->firstComp + 1)
#define B(pixel) *(pixel->firstComp + 2)

namespace npcv {

	enum PixelType {
		GRAY = 1,
		GA = 2,
		RGB = 3,
		RGBA = 4
	};


	class Pixel {
	public:
		Pixel(unsigned char* firstComp, PixelType type) : firstComp(firstComp), type(type) {};
		PixelType type;
		unsigned char* firstComp;
	};

	class Image
	{
	public:
		Image();
		Image(int width, int height, PixelType type);
		Image(unsigned char* data, int width, int height, PixelType type);
		~Image();

		unsigned char* pixels;
		int width;
		int height;
		PixelType type;

		Pixel* pixelAt(int x, int y);

		unsigned char* pixelAt_ptr(int x, int y);

		void pixelSet(int x, int y, int r, int g, int b);

		void pixelSet(int x, int y, Pixel* value);

		void pixelSet_ptr(int x, int y, unsigned char* firstComp);


		Image* getSubImage(int x, int y, int width, int height);
	};

}

