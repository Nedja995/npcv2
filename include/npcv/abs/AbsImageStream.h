#ifndef _ABS_IMAGE_STREAM__
#define _ABS_IMAGE_STREAM__

#include "AbsImage.h"

namespace npcv {

	class AbsImageSteam {
	public:
		virtual ~AbsImageSteam() = 0;

		virtual AbsImage* Load(const char* path) = 0;

		virtual bool Save(AbsImage* image, const char* path) = 0;

		virtual void Free() = 0;
	};


}
#endif