#include "Treshold.h"
namespace npcv {namespace segmentation {

	bool Treshold::global(Image* image, int intensity)
	{
		image->convertToGrayscale();
		Image* tresh = new Image(image->width, image->height, image->type);

		for (int x = 0; x < image->width; x++) {
			for (int y = 0; y < image->height; y++) {
				Pixel* px = image->pixel(x, y);
				int val = R(px);
				if (val < intensity) {
					R(tresh->pixel(x, y)) = 0;
					//tresh->pixel(x, y)->r(borderValue);
				}
				else {
					R(tresh->pixel(x, y)) = 255;
				}
			}
		}
		free(image->pixels);
		image->pixels = tresh->pixels;
		return true;
	}
}
}