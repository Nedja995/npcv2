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

			virtual void initialize() override;

			// Inherited via IProcessImage
			virtual void processImage() override;

		protected:
			static bool matrixApply(Image* image);
		};
	}
}

