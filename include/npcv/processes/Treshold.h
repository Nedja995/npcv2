#pragma once
#include "npcv/types/Image.h"
namespace npcv {
	namespace segmentation {

	/**
	 * @class	ImageTresholding
	 *
	 * @brief	Provide static methods for image treshloding.
	 * @todo	Implement Adaptive Mean and Gausian Tresholding
	 */
	static class Treshold {
	public:

		/**
		 * @brief	Apply global treshold based on one intensity param.
		 *
		 * @param [in,out]	image	Image to apply.
		 * @param	intensity	 	The intensity.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		static bool global(Image* image, int intensity);
	};

}
}