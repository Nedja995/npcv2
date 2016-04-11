#pragma once
#include <vector>
#include "npcv/types/Image.h"
namespace npcv {
	namespace sampling {
		std::vector<Image*> Subimages(Image& image, int sampleWidth, int sampleHeight);
	}
}