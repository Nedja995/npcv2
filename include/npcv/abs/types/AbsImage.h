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
		virtual ~AbsImage() = 0;

		virtual void* GetData() = 0;

		virtual ulint GetMemSize() = 0;

		virtual int GetWidth() = 0;
		
		virtual int GetHeight() = 0;
	
		virtual ImageType GetType() = 0;

		virtual Pixel* GetPixels() = 0;

	};
}

#endif