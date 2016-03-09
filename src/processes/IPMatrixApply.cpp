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

			//temporals
			int mat = 0;
			int index = 0;
			int imageX = 0;
			int imageY = 0;
			float red = 0.0f, green = 0.0f, blue = 0.0f;
			int r = 0, g = 0, b = 0;
		    Pixel *pixel = 0; //curent center pixel
			Pixel *pixelProc = 0; //curent pixel that is processing with filter
			for (int x = 0; x < image->width; x++) {
				for (int y = 0; y < image->height; y++)
				{
					index = 0;
					red = 0.0f, green = 0.0f, blue = 0.0f;
					//iterate throught matrix
					for (int mx = 0; mx < matrixSize; mx++) {
						for (int my = 0; my < matrixSize; my++)
						{
							imageX = (x - matrixSize / 2 + mx + image->width) % image->width;
							imageY = (y - matrixSize / 2 + my + image->height) % image->height;
							pixelProc = image->pixel(imageX, imageY);

							mat =  *(matrix + index++);

							red += R(pixelProc) * mat;
							green += G(pixelProc) * mat;
							blue += B(pixelProc) * mat;

							delete pixelProc;
						}
					}
					pixel = image->pixel(x, y);
					r = std::min(std::max(int(factor * red + bias), 0), 255);
					g = std::min(std::max(int(factor * green + bias), 0), 255);
					b = std::min(std::max(int(factor * blue + bias), 0), 255);
					ret->pixel(x,y)->setColor(r, g, b);
					
					delete pixel;
				}
			}
			image->pixels = ret->pixels;
			return true;
		}
	}
}
