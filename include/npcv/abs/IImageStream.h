#ifndef _ABS_IMAGE_STREAM__
#define _ABS_IMAGE_STREAM__

#include "npcv/types/Image.h"
#include <string>
namespace npcv {

	class IImageStream {
	public:

		//virtual ~IImageStream() = 0;

		virtual Image& Load(std::string path) = 0;

		virtual bool Save(Image& image, std::string path) = 0;

		virtual void free() = 0;
	};


}
#endif
