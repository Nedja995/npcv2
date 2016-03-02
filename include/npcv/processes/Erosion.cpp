#include "Erosion.h"
#include <iostream>
#include <string>
namespace npcv {
namespace processing {

	Image * Erosion::erosion(Image * imageGray, int size, int foregroundValue, int iteration, std::function<void(Image*)> iterationResults )
	{
		Image* ret = new Image(imageGray->width, imageGray->height, imageGray->type);
		ret->setColor(255 - foregroundValue, 255 - foregroundValue, 255 - foregroundValue);
		Image* image = new Image(imageGray);
		iterationResults(image);
		int mx = 0, my = 0; //nearby pixel iterators
		bool changed = true, surounded = true;
		Pixel *center = 0, *mpx = 0; //center and nearby pixels

		int i = 0;
		while (changed) {
			changed = false;
			std::cout << "Iter" << std::endl;
			//Iterate over pixels
			for (int x = size; x < image->width - size; x++) {
			for (int y = size; y < image->height - size; y++) {
				center = image->pixelAt(x, y);
				//Looking for foreground pixel
				if (R(center) != foregroundValue) 
					continue;
					
				//Check nearby pixels to confirm that is surounded with foreground
				
				for (mx = -size; mx < size; mx++) {
				for (my = -size; my < size; my++) {
					mpx = image->pixelAt(x + mx, y + my); //nearby pixel
					//Not surounded by foreground
					if (R(mpx) != R(center)) {
						surounded = false;
						
						delete mpx;
						break;
					}
					delete mpx;
				}
				if (surounded) break;
				}//end iterate nerby

				delete center;

				//Draw filtered foreground pixel
				if ( surounded ) {
					ret->pixelSet(x, y, foregroundValue, foregroundValue, foregroundValue);
					changed = true;
				}
				else {
					//ret->pixelSet(x, y, 255 - foregroundValue, 255 - foregroundValue, 255 - foregroundValue);
				}

				surounded = true;
			}
			}//end iterate pixels

		//	if (i++ == iteration) {
			//	changed = false;
			//}
			if ( changed ) {
				//free old image
				delete image;
				//Iterate again over filtered image
				image = ret;
				
				if (iterationResults != 0) {
					iterationResults(ret);
				}
				

				ret = new Image(imageGray->width, imageGray->height, imageGray->type);
			}
			else {
				break;
			}
		}//end iteration

		return ret;
	}
}
}