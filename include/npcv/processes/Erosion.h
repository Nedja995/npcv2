#pragma once

#include "npcv/types/Image.h"
#include <functional>
namespace npcv {
namespace processing {

	class Erosion {
	public:
		static void erosion(Image& grayImage, int size, Pixel& foregroundPixel, std::function<void(Image&)> iterationResults);

	};

}
}