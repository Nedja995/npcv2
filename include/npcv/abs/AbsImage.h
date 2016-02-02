#ifndef _ABS_IMAGE__
#define _ABS_IMAGE__

namespace npcv {
	
	typedef unsigned char uchar;
	typedef unsigned long int ulint;

	enum ImageType {
		BGR = 0
	};

	class Pixel {
	public:
		uchar * firstComponent;
		int components;

		Pixel(uchar* firstComponent, int components)
			: firstComponent(firstComponent)
			, components(components) {}

		virtual ~Pixel() {};
	};



	class AbsImage {
	public:
		virtual ~AbsImage() {};

		virtual void* getData() = 0;

		virtual ulint getMemSize() = 0;

		virtual int getWidth() = 0;
		
		virtual int getHeight() = 0;
	
		virtual ImageType getType() = 0;

		virtual Pixel* getPixels() = 0;

	};
}

#endif