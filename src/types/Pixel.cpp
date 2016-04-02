#include "npcv/types/Pixel.h"
#include <iostream>

namespace npcv {



	
	Pixel & Pixel::Create(PixelType type)
	{
		Pixel& ret = *new Pixel();
		ret.type = type;
		ret.colorPtr = new uchar[type]{ 255 };
		ret._allocated = true;
		return ret;
	}

	Pixel & Pixel::Create(uchar * components, PixelType type)
	{
		// TODO: insert return statement here
		Pixel& ret = *new Pixel();
		ret.type = type;
		ret.colorPtr = new uchar[type];
		ret._allocated = true;
		memcpy(ret.colorPtr, components, sizeof(uchar) * type);

		return ret;
	}

	Pixel & Pixel::Create(uchar * components, PixelType type, bool isPointer)
	{
		Pixel& ret = *new Pixel();
		ret.type = type;
		ret.colorPtr = components;
		ret._allocated = false;
		return ret;
	}

	Pixel & Pixel::Create(int g)
	{
		Pixel& ret = *new Pixel();
		ret.type = GRAY;
		ret.setColor(g);
		return ret;
	}

	Pixel & Pixel::Null()
	{
		Pixel& ret = *new Pixel();
		return ret;
	}

	Pixel::Pixel()
	{
		colorPtr = nullptr;
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
		if (_allocated) {
			delete [] colorPtr;
		}
	//	

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
		if(colorPtr != nullptr){
			
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

	bool Pixel::setColor(Pixel& pixel)
	{
		if (!_assertTypeStrict(pixel.type)) {
			// Cannot set XX pixel type to XX 
			return false;
		}
		if (pixel.type == GRAY) {
			setColor(pixel.color(0));
			return true;
		}
		else if (pixel.type == RGB) {
			setColor(pixel.color(0), pixel.color(1), pixel.color(2));
			return true;
		}
		else {
			std::cerr << "npcv:Pixel:setColor: Unknown type";
			return false;
		}
		
		return false;
	}

	bool Pixel::setColor(int g)
	{
		if (!_assertType(GRAY)) { 	
		}

		if (colorPtr == nullptr) {
			colorPtr = new uchar[1];
			_allocated = true;
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