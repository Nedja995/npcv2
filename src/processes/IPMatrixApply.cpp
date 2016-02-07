#include "npcv/processes/IPMatrixApply.h"
#include "npcv/types/Image.h"
#include <iostream>
#include <algorithm>
namespace npcv {
	namespace processing {

		IPMatrixApply::IPMatrixApply()
		{
			matrix = 0;
			matrixSize = -1;
		}


		void IPMatrixApply::initialize()
		{
			IProcessImage::initialize();
			if (matrix == 0) {
				std::cerr << "npcv: IPMatrixApply::initialize: missing matrix" << std::endl;
				_initialized = false;
			}
			if (matrixSize == -1) {
				std::cerr << "npcv: IPMatrixApply::initialize: missing matriSize" << std::endl;
				_initialized = false;
			}
			
		}

		void IPMatrixApply::processImage()
		{
			matrixApply(_image);
		}

		bool IPMatrixApply::matrixApply(Image * image)
		{
			Image * ret = new Image(image->width, image->height, image->type);

			const int filterWidth = 3;
			const int filterHeight = 3;
			float filter[filterWidth][filterHeight] =
			{
				1,  1,  1,
				1, -7,  1,
				1,  1,  1
			};

			/* Multiply result with factor */
			float factor = 1.0 ;
			/* Make image brightnes */
			float bias = 0.0;

			//temporals
		    Pixel *pixel = 0; //curent center pixel
			Pixel *pixelProc = 0; //curent pixel that is processing with filter
			for (int x = 0; x < image->width; x++) {
				int a = 3;
				for (int y = 0; y < image->height; y++)
				{

					float red = 0.0f, green = 0.0f, blue = 0.0f;
					//iterate throught matrix
					for (int mx = 0; mx < filterWidth; mx++) {
						for (int my = 0; my < filterHeight; my++)
						{
							int imageX = (x - filterWidth / 2 + mx + image->width) % image->width;
							int imageY = (y - filterHeight / 2 + my + image->height) % image->height;
							pixelProc = image->pixelAt(imageX, imageY);
							red += R(pixelProc) * filter[mx][my];
							green += G(pixelProc) * filter[mx][my];
							blue += B(pixelProc) * filter[mx][my];
							delete pixelProc;
						}
					}
					pixel = image->pixelAt(x, y);
					int r = std::min(std::max(int(factor * red + bias), 0), 255);
					int g = std::min(std::max(int(factor * green + bias), 0), 255);
					int b = std::min(std::max(int(factor * blue + bias), 0), 255);
					ret->pixelSet(x, y, r, g, b);
					
					//R(pixel) = std::fminf(std::fmaxf(int(factor * red + bias), 0), 255);
					//G(pixel) = std::fminf(std::fmaxf(int(factor * green + bias), 0), 255);
					//B(pixel) = std::fminf(std::fmaxf(int(factor * blue + bias), 0), 255);
					delete pixel;
				}
			}
			image->pixels = ret->pixels;
			return true;
		}
	}
}
