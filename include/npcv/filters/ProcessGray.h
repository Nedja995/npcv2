#pragma once
#include "IProcessImage.h"
#include "npcv/types/Image.h"
namespace npcv { namespace processing {

	class ProcessGray : public IProcessImage
	{
	public:

		// Inherited via IProcessImage
		virtual void processImage() override;

		int getIntensity();

		void setIntensity(int value);

	protected:
		int _intensity;

		static bool divideImagePixels(Image* image, int intensity);
		static bool divideImagePixels2(Image* image, int intensity);




	};

}
}

