#include <iostream>
#include "npcv/freatures/EdgeDetectCanny.h"
namespace npcv {
	namespace freatures {
		Image & npcv::freatures::Canny(Image & gray, int resolution, int sensitivity, int edgeColor, bool vertical)
		{
			if (gray.type != GRAY) {
				std::cerr << "npcv:CannyVertical: Image not gray" << std::endl;
				return Image::Null();
			}
			Image& ret = Image::Create(gray.width, gray.height, GRAY);
			ret.setColor(edgeColor, edgeColor, edgeColor);
			// X
			for (int x = 0; x < gray.width; ++x){
			for (int y = 0; y < gray.height; ++y){
				if (x < resolution + 1 || x + resolution + 1 > gray.width
					|| y < resolution + 1 || y + resolution + 1 > gray.height)
				{
					continue;
				}

				int center = *gray.pixelPtr(x, y);

				int left = 0; 
				int right = 0;
				if (vertical) {
					left = *gray.pixelPtr(x - resolution, y);
					right = *gray.pixelPtr(x + resolution, y);
				}
				else {
					left = *gray.pixelPtr(x, y - resolution);
					right = *gray.pixelPtr(x, y + resolution);
				}
				if (/*abs(*/center - left/*)*/ < sensitivity
					|| /*abs(*/center - right/*)*/ < sensitivity)
				{
					ret.setPixel(x, y, 255 - edgeColor);
				}
				else
				{
					//edge
					ret.setPixel(x, y, edgeColor);
				}
			}
			}
			return ret;
		}
	}
}