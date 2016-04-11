#include <iostream>
#include "npcv/classification/RegionEdge.h"

namespace npcv {
	namespace classify {
		std::vector<int> GetRegions(Image& edges, int width, int height, int edgeColor)
		{
			auto ret = std::vector<int>();
			if (edges.type != GRAY) {
				std::cerr << "npcv:GetRegions: Image not gray" << std::endl;
				return ret;
			}

			Image* regImg = nullptr;
			int regValue = 0;
			for (int x = 0; x < edges.width - width; x+= width) {
				for (int y = 0; y < edges.height - height; y += height) {
					regImg = &edges.getSubImage(x, y, width, height);
					for_each_pixelPtr((*regImg))
						if (*pixelPtr == edgeColor) {
							regValue++;
						}
					for_each_pixelPtr_end
					ret.push_back(regValue);
				}
			}

			return ret;
		}
	}
}