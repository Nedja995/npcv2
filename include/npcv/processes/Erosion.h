#pragma once

#include "npcv/types/Image.h"
#include <functional>
namespace npcv {
namespace processing {

	class Erosion {
	public:
		static Image* erosion(Image* imageGray, int size, int foregroundValue, int iteration, std::function<void(Image*)> iterationResults);
	};

}
}