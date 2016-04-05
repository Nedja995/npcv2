#include "Treshold.h"
namespace npcv {namespace segmentation {

	bool Treshold::global(Image& image, int intensity)
	{
		image.convertToGrayscale();
		Image& tresh = Image::Create(image.width, image.height, image.type);

		for_each_pixelPtr(image)
			if (*(pixelPtr) < intensity) {
				tresh.setPixel(x, y, 0);
			}
			else {
				tresh.setPixel(x, y, 255);
			}
		for_each_pixelPtr_end

		// Slow
/*		for (int x = 0; x < image.width; x++) {
			for (int y = 0; y < image.height; y++) {
				Pixel& px = image.pixel(x, y);
				int val = px.color(0);
				if (val < intensity) {
					Pixel& px2 = Pixel::Create(0);
					tresh.setPixel(x, y, px2);
					delete &px2;
				}
				else {
					Pixel& px2 = Pixel::Create(255);
					tresh.setPixel(x, y, px2);
					delete &px2;
				}
				delete &px;
			}
		}
*/

		image.setPixelsCopy(tresh);
		delete &tresh;
		return true;
	}
}
}