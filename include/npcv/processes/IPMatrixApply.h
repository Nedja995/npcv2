#pragma once
#include "IProcessImage.h"
namespace npcv {
	namespace processing {
		class IPMatrixApply : public IProcessImage
		{
		public:
			IPMatrixApply(); 

			int matrixSize;
			float *matrix;
			/* Multiply result with factor */
			float factor = 1.0;
			/* Make image brightnes */
			float bias = 0.0;

			virtual void initialize() override;

			// Inherited via IProcessImage
			virtual void processImage() override;

		protected:
			bool matrixApply(Image* image);
		};
	}
}

