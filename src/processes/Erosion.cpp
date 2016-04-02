#include "npcv/processes/Erosion.h"
#include <iostream>
#include <string>
namespace npcv {
namespace processing {

	void Erosion::erosion(Image& imageGray, int size, Pixel& foregroundPixel, std::function<void(Image&)> iterationResults) {

		Image& current = Image::Create(imageGray);
		//Image to write pixel that is surrounded by same pixel (foreground)
		Image& next = Image::Create(imageGray.width, imageGray.height, imageGray.type);
		next.setColor(255 - foregroundPixel.color(0), 255 - foregroundPixel.color(0), 255 - foregroundPixel.color(0));

		bool changed = true, surounded = false;
		int mx, my;

		//Loop while no one pixels writen to next step image
		while (changed) {
			std::cout << "iter" << std::endl;
			changed = false;
			//Iterate throught current step image pixels
			for (int x = size; x < current.width - size; x++) {
			for (int y = size; y < current.height - size; y++) {
				//Check is foreground
				if (current.pixel(x, y) == foregroundPixel) {
					//if foreground - Check is surrounded with foreground pixels
					surounded = true;
					for (mx = -size; mx < size; mx++) {
					for (my = -size; my < size; my++) {
						Pixel& nearbyPx = current.pixel(x + mx, y + my, true);
						if (nearbyPx != foregroundPixel) {
							surounded = false;
						}
						delete &nearbyPx;
					}
					}//end check surounded iters
					//if surrounded - draw current foreground pixel to next step image
					if (surounded) {
						Pixel& px = next.pixel(x, y, true);
						px.setColor(foregroundPixel);
						delete &px;
						changed = true;
					}
				}
			}
			}//end image iterations
			//delete &current;
			current = next;
			//delete &next;
			next = Image::Create(imageGray.width, imageGray.height, imageGray.type);
			next.setColor(255 - foregroundPixel.color(0), 255 - foregroundPixel.color(0), 255 - foregroundPixel.color(0));
			iterationResults(current);
			//If change happened - go to next step
				//Set next step image to current image
				//Create new next step image
			//If not change happened break loop - last iteration
		}

		iterationResults(current);
		delete &current;
	}

}
}