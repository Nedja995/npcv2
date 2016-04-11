#pragma once

#include "npcv/abs/IProcess.h"
#include "npcv/types/Image.h"

namespace npcv { namespace processing {

	/**
	 * @class	IProcessImage
	 *
	 * @brief	The process image.
	 */
	class IProcessImage : public IProcess
	{
	public:
		IProcessImage();

		/**
		 * @brief	Gets the image.
		 *
		 * @return	null if it fails, else the image.
		 */
		virtual Image* getImage();

		/**
		 * @brief	Sets an image.
		 *
		 * @param [in,out]	image	If non-null, the image.
		 */
		virtual void setImage(Image* image);

		/**
		 * @brief	Process the image.
		 */
		virtual void processImage() = 0;

		
		virtual void initialize() override;
		virtual bool isInitialized() override;
		virtual void execute() override;
		virtual bool isProcessing() override;
		virtual void free() override;

	protected:
		Image* _image;

		bool _initialized;
		bool _processing;
	};


}
}

