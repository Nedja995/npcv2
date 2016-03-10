#include "Treshold.h"
namespace npcv {namespace segmentation {

	bool Treshold::global(Image& image, int intensity)
	{
		image.convertToGrayscale();
		Image tresh = Image::Create(image.width, image.height, image.type);

		for (int x = 0; x < image.width; x++) {
			for (int y = 0; y < image.height; y++) {
				Pixel& px = image.pixel(x, y);
				int val = px.color(0);
				if (val < intensity) {
					tresh.pixel(x, y).setColor(0);
					//tresh->pixel(x, y)->r(borderValue);
				}
				else {
					tresh.pixel(x, y).setColor(255);
				}
			}
		}

		image.setPixelsCopy(tresh);

		return true;
	}
}
}