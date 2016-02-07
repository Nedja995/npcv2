#pragma once



#define R(pixel) *(pixel->firstComp )
#define G(pixel) *(pixel->firstComp + 1)
#define B(pixel) *(pixel->firstComp + 2)

namespace npcv {

	typedef unsigned char uchar;

	enum PixelType {
		GRAY = 1,
		GA = 2,
		RGB = 3,
		RGBA = 4
	};


	class Pixel {
	public:
		Pixel(uchar* firstComp, PixelType type) : firstComp(firstComp), type(type) {};
		PixelType type;
		uchar* firstComp;
	};

	class Image
	{
	public:
		Image();
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


		Image* getSubImage(int x, int y, int width, int height);
	};

}

