#ifndef _UTILS_IMAGESTREAM_STB__
#define _UTILS_IMAGESTREAM_STB__
#include "../abs/IImageStream.h"
namespace npcv {
	namespace utils {

		class ImageStreamSTB : IImageSteam {
		public:
			ImageStreamSTB();
			// Inherited via IImageSteam
			virtual Image * Load(const char * path) override;
			virtual bool Save(Image * image, const char * path) override;
			virtual void free() override;
		};
	}


}
#endif