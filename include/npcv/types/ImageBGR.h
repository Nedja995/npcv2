#ifndef _ABS_IMAGE_BGR__
#define _ABS_IMAGE_BGR__

#include "../abs/AbsImage.h"

namespace npcv {

	namespace types {

		class PixelGBR : public Pixel {
		public:
			int r, g, b;
			PixelGBR(uchar* firstComponent, int b, int g, int r)
				: Pixel(firstComponent, 3)
				, r(r), g(g), b(b) {}

		};

		class ImageBGR : public AbsImage {
		public:
			ImageBGR(ImageBGR& image);
			
			ImageBGR(uchar* data, int width, int height);

			virtual ~ImageBGR() override;

			// Inherited via AbsImage
			virtual void * getData() override;

			virtual ulint getMemSize() override;

			virtual int getWidth() override;

			virtual int getHeight() override;

			virtual ImageType getType() override;

			virtual Pixel * getPixels() override;

		protected:
			int _width;
			int _height;
			uchar* _data;
		};

	}

}
#endif