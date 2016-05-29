#include "npcv/morphology/Erosion.h"
#include <iostream>
#include <string>
namespace npcv {
namespace processing {

	void Erosion::erosion(Image& imageGray, int size, Pixel& foregroundPixel, std::function<void(Image&)> iterationResults) {
		if (imageGray.type != GRAY) {
			imageGray.convertToGrayscale();
		}
		int foregroundValue = foregroundPixel.color(0);
		Image* current = &Image::Create(imageGray);
	//	iterationResults(*current);
		//Image to write pixel that is surrounded by same pixel (foreground)
		Image* next = &Image::Create(imageGray.width, imageGray.height, imageGray.type);
	//	iterationResults(*next);
		next->setColor(255 - foregroundValue, 255 - foregroundValue, 255 - foregroundValue);
	//	iterationResults(*next);
		//Loop while no one pixels writen to next step image
		bool changed = true, surounded = false;
		int mx, my;
		while (changed) {
			std::cout << "iter" << std::endl;
			changed = false;
			//Iterate throught current step image pixels
			for (int x = size; x < current->width - size; x++) {
			for (int y = size; y < current->height - size; y++) {
				//Check is foreground
				uchar* px = current->pixelPtr(x, y);
				if (*(px) == foregroundValue) {
					//if foreground - Check is surrounded with foreground pixels
					surounded = true;
					for (mx = -size; mx < size; mx++) {
					for (my = -size; my < size; my++) {
						uchar* nearbyPx = current->pixelPtr(x + mx, y + my);
						if (*(nearbyPx) != foregroundValue) {
							surounded = false;
						}
					}
					}//end check surounded iters
					//if surrounded - draw current foreground pixel to next step image
					if (surounded) {
						next->setPixel(x, y, foregroundValue);
						changed = true;
					}
				}
			}
			}//end image iterations

			// Slow
/*			for (int x = size; x < current->width - size; x++) {
			for (int y = size; y < current->height - size; y++) {
				//Check is foreground
				if (current->pixel(x, y) == foregroundPixel) {
					//if foreground - Check is surrounded with foreground pixels
					surounded = true;
					for (mx = -size; mx < size; mx++) {
					for (my = -size; my < size; my++) {
						Pixel& nearbyPx = current->pixel(x + mx, y + my, true);
						if (nearbyPx != foregroundPixel) {
							surounded = false;
						}
						delete &nearbyPx;
					}
					}//end check surounded iters
					//if surrounded - draw current foreground pixel to next step image
					if (surounded) {
						Pixel& px = next->pixel(x, y, true);
						px.setColor(foregroundPixel);
						delete &px;
						changed = true;
					}
				}
			}
			}//end image iterations
*/
				

			current->setPixelsCopy(*next);
			
			delete next;
			next = &Image::Create(imageGray.width, imageGray.height, imageGray.type);
			next->setColor(255 - foregroundValue, 255 - foregroundValue, 255 - foregroundValue);
			iterationResults(*current);
			//If change happened - go to next step
				//Set next step image to current image
				//Create new next step image
			//If not change happened break loop - last iteration

		}// END ITERATION
		iterationResults(*current);
		delete next;
		delete current;
	}//end function

}
}