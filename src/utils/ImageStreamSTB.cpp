#include "npcv/Toolset.h"
#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/types/Image.h"
#include <iostream>


#define NPCV_STB_IMAGE

#ifdef NPCV_STB_IMAGE
#define STB_IMAGE_IMPLEMENTATION
#include "thirdparty/stb/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "thirdparty/stb/stb_image_write.h"
#endif

namespace npcv {
	namespace utils {

		using namespace std;

	//	mageStreamSTB::~ImageStreamSTB()
	//	{
	//	}

		ImageStreamSTB::ImageStreamSTB()
		{
		}

		Image * ImageStreamSTB::Load(const char * path)
		{
			int width, height, type;
			Image * ret = 0;

#ifdef NPCV_STB_IMAGE
			//load image with stb
			unsigned char * data = stbi_load(path, &width, &height, &type, 3);
			if (data == 0) {
				cerr << "NPCV: ImageStreamSTB: cannot load image from: " << path;
			}
			ret = new Image(data, width, height, (PixelType)type);
#endif
			return ret;

		}

		bool ImageStreamSTB::Save(Image * image, const char * path)
		{
			int res = stbi_write_png(path,
				image->width,
				image->height,
				image->type,
				image->pixels,
				0);

			if (res == 0) {
				cerr << "NPCV: ImageStreamSTB: cannot save image to: " << path;
				return false;
			}

			return true;
		}

		void ImageStreamSTB::free()
		{
		}

	}
}
