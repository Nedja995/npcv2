#include "npcv/types/Pixel.h"


namespace npcv {



	
	Pixel & Pixel::Null()
	{
		Pixel& ret = *new Pixel();
		return ret;
	}

	Pixel::Pixel()
	{
	}

	Pixel::Pixel(Pixel * pixel, bool copy)
	{
		_allocated = copy;
		type = pixel->type;
		if (copy) 
		{
			colorPtr = new uchar[type];
			for (int i = 0; i <= type; i++) {
				colorPtr[i] = *(pixel->colorPtr + i);
			}
		}
		else 
		{
			colorPtr = pixel->colorPtr;
		}
	}

	Pixel::~Pixel()
	{
		//if (allocated) {
		//	delete colorPtr;
		//}
	}

	bool Pixel::isPointer()
	{
		return !_allocated;
	}

	int Pixel::color(int index)
	{
		if (!_assertType(static_cast<PixelType>(index))) { 
			return 0; 
		}
		return static_cast<int>(*(colorPtr + index));
	}

	bool Pixel::setColor(int r, int g, int b)
	{
		if (!_assertType(RGB)) { 
			return false; 
		}

		*(colorPtr) = r;
		*(colorPtr + 1) = g;
		*(colorPtr + 2) = b;

		return true;
	}

	bool Pixel::setColor(Pixel * pixel)
	{
		if (!_assertTypeStrict(pixel->type)) {
			// Cannot set XX pixel type to XX 
			return false;
		}
		for (int i = 0; i < type; i++) {
			*(colorPtr + i) = *(pixel->colorPtr + i);
		}
		return true;
	}

	bool Pixel::setColor(int g)
	{
		if (!_assertType(GRAY)) { 	
		}

		*(colorPtr) = g;
		return true;
	}

	bool Pixel::_assertTypeStrict(PixelType target)
	{
		//check type
		// TODO: add other type checks and debug message
		if (type != target) {
			return false;
		}

		return true;
	}

	bool Pixel::_assertType(PixelType target)
	{
		//check type
		// TODO: add other type checks and debug message
		if (type < target) {
			return false;
		}
		return true;
	}


}