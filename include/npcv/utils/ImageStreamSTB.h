#ifndef _UTILS_IMAGESTREAM_STB__
#define _UTILS_IMAGESTREAM_STB__
#include "npcv/abs/AbsImageStream.h"
namespace npcv {
	namespace utils {

		class ImageStreamSTB : AbsImageSteam {
			// Inherited via AbsImageSteam
			virtual AbsImage * Load(const char * path) override;
			virtual bool Save(AbsImage * image, const char * path) override;
			virtual void Free() override;
		};
	}


}
#endif