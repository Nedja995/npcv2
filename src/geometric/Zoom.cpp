#include "npcv/geometric/Zoom.h"
#include <math.h>
namespace npcv {
	namespace geometric {
		bool Replication(Image& image, float scaleX, float scaleY)
		{
			
			int sWidth = image.width * scaleX;
			int sHeight = image.height * scaleY;
			Image& scaled = Image::Create(sWidth, sHeight, image.type);

			//iterate over empty scaled image and fill with coresponding pixel from original
			for (int x = 0; x < sWidth; x++) {
			for (int y = 0; y < sHeight; y++) {
				//find pixel original

				int xOrig = std::floor(x / scaleX);
				int yOrig = std::floor(y / scaleY);
				uchar* pxOrig = image.pixelPtr(xOrig, yOrig);
				//copy pixel components
				uchar* pxScaled = scaled.pixelPtr(x, y);
				for (int i = 0; i < image.type; i++) {
					*(pxScaled + i) = *(pxOrig + i);
				}
			}
			}
			image.Clone(scaled);
			delete &scaled;

			return false;
		}
	}
}