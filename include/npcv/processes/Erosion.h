#pragma once

#include "npcv/types/Image.h"

namespace npcv {
namespace processing {

	class Erosion {
	public:
		static Image* erosion(Image* imageGray, int size, int foregroundValue, int iteration);
	};

}
}