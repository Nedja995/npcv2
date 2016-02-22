#ifndef _UTILS_IMAGESTREAM_STB__
#define _UTILS_IMAGESTREAM_STB__
#include "../abs/IImageStream.h"
#include <string>
namespace npcv {
	namespace utils {

		class ImageStreamSTB : IImageStream {
		public:
			ImageStreamSTB();
			//virtual ~ImageStreamSTB() override;
			// Inherited via IImageStream
			virtual Image * Load(std::string path) override;
			virtual bool Save(Image * image, std::string path) override;
			virtual void free() override;
		};
	}


}
#endif
