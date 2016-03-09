#pragma once
#include "IProcessImage.h"

namespace npcv {
	namespace processing {

		/**
		* @brief	Blends.
		*
		* @param [in,out]	first 	First Image.
		* @param [in,out]	second	Second Image.
		* @param	ratio		  	The ratio.
		*
		* @return	null if it fails, else an new Image*.
		*/
		static Image * Blend(Image * first, Image * second, float ratio)
		{
			Image* ret = new Image(first->width, first->height, first->type);

			for (int x = 0; x < first->width; x++) {
				for (int y = 0; y < first->height; y++) {
					Pixel* fp = first->pixel(x, y);

					int r11 = R(fp);
					int g11 = G(fp);
					int b11 = B(fp);

					Pixel* sp = second->pixel(x, y);
					Pixel px = Pixel(*fp);
					Pixel px2 = Pixel(*sp);

					int r1 = R((&px));
					int g1 = G((&px));
					int b1 = B((&px));

					int r2 = R((&px2));
					int g2 = G((&px2));
					int b2 = B((&px2));

					//Pixel newPX = px + px2;
					//Pixel newPX = 0; px * 3;

					//int r =  R((&newPX));
					//int g = G((&newPX));
					//int b =  B((&newPX));
					//ret->pixelSet(x, y, &newPX);
				}
			}
			return ret;
		}

		/**
		 * @class	IPBlending
		 *
		 * @brief	Blending Image Process.
		 */
		class IPBlending : public IProcessImage
		{
		public:



			/** @brief	The ratio. Value betwen 0 - 1 */
			float ratio;

			/**
			 * @brief	Constructor.
			 *
			 * @param [in,out]	first 	First image.
			 * @param [in,out]	second	Second image.
			 */
			IPBlending(Image* first, Image* second);

			/**
			 * @brief	Default constructor.
			 */
			IPBlending();

			/**
			 * @brief	Destructor.
			 */
			~IPBlending();

			/**
			 * @brief	Sets second image.
			 *
			 * @param [in,out]	image	If non-null, the image.
			 */
			void setSecondImage(Image* image);

			/**
			 * @brief	Gets second image.
			 * @return	null if it fails, else the second image.
			 */
			Image* getSecondImage();

			// Inherited via IProcessImage
			virtual void processImage() override;

			virtual void initialize() override;
		protected:
			Image* _imageSecond;



		};



	}
}


