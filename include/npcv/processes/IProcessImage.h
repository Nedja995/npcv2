#pragma once

#include "npcv/abs/IProcess.h"
#include "npcv/types/Image.h"

namespace npcv { namespace processing {

	class IProcessImage : public IProcess
	{
	public:
		IProcessImage();

		virtual Image* getImage();
		virtual void setImage(Image* image);

		virtual void processImage() = 0;

		// Inherited via IProcess
		//virtual ~IProcessImage() override;
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

