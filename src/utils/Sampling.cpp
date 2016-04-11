#include "npcv/utils/Sampling.h"
namespace npcv {
	namespace sampling {
		std::vector<Image*> Subimages(Image & image, int sampleWidth, int sampleHeight)
		{
			std::vector<Image*> ret = std::vector<Image*>();
			for (int x = 0; x < image.width - sampleWidth; x += sampleWidth)
			{
				for (int y = 0; y < image.height; y += sampleHeight)
				{
					Image& sub = image.getSubImage(y, x, sampleWidth, sampleHeight);
					if (sub.type != Null) {

						ret.push_back(&sub);
					}
					else {
						delete &sub;
					}
				}
			}
			return ret;
		}
	}
}