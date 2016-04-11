#pragma once
#include "npcv/types/Image.h"

namespace npcv {
	namespace freatures {
		Image& Canny(Image& gray, int resolution, int sensitivity, int edgeColor, bool vertical);
	}
}