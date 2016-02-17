#ifndef _ABS_IMAGE_STREAM__
#define _ABS_IMAGE_STREAM__

#include "npcv/types/Image.h"

namespace npcv {

	class IImageStream {
	public:

		//virtual ~IImageStream() = 0;

		virtual Image* Load(const char* path) = 0;

		virtual bool Save(Image* image, const char* path) = 0;

		virtual void free() = 0;
	};


}
#endif
