#pragma once
#include "npcv/types/Image.h"
#include <vector>
namespace npcv {
	namespace classify {
		std::vector<int> GetRegions(Image& edges, int width, int height, int edgeColor);
	}
}