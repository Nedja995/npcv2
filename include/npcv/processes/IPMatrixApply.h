#pragma once
#include "IProcessImage.h"
namespace npcv {
	namespace processing {

		class IPMatrixApply : public IProcessImage
		{
		public:

			/**
			 * @brief	Default constructor.
			 */
			IPMatrixApply(); 
			
			int matrixSize;

			float *matrix;

			float factor = 1.0;

			float bias = 0.0;

			virtual void initialize() override;

			virtual void processImage() override;

		protected:
			bool matrixApply(Image* image);
		};
	}
}

