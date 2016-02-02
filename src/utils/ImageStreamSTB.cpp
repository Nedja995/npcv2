#include "npcv/Toolset.h"
#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/types/ImageBGR.h"
#include <iostream>


#define NPCV_STB_IMAGE

#ifdef NPCV_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb/stb_image.h"
#endif

namespace npcv {
	namespace utils {

		using namespace npcv::types;

		AbsImage * ImageStreamSTB::Load(const char * path)
		{
			int width, height, type;
			ImageBGR * ret = 0;

#ifdef NPCV_STB_IMAGE
			//load image with stb
			unsigned char * data = stbi_load(path, &width, &height, &type, 3);
			if (data == 0) {
				npcv::DebugLog((std::string("NPCV: ImageStreamSTB: cannot load image from: ") + std::string(path)).c_str());
			}
			ret = new ImageBGR(data, width, height);
#endif
			return ret;

		}

		bool ImageStreamSTB::Save(AbsImage * image, const char * path)
		{
			return false;
		}

		void ImageStreamSTB::Free()
		{
		}

	}
}