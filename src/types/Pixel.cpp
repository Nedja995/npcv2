#include "npcv/types/Pixel.h"


namespace npcv {



	
	Pixel::Pixel(Pixel * pixel, bool copy)
	{
		allocated = copy;
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

}