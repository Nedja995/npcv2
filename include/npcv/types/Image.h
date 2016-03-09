#pragma once

#include "Pixel.h"

#include <string>
#include <functional>

#include <algorithm>

/**
 * @def	for_each_pixel(image) for(int x = 0;
 *
 * @brief	Start macro for iterating over image pixels. Use also for_each_pixel_end !
 *
 * @param	image	The image.
 */
#define for_each_pixel(image) \
	for(int x = 0; x < image->width; x++) { \
	for(int y = 0; y < image->height; y++) { \
		Pixel* pixel = image->pixel(x, y);
 /**
 * @def	for_each_pixel_end	delete pixel;}}
 *
 * @brief	End macro for iterating over image pixels.
 */
#define for_each_pixel_end	delete pixel;}}

namespace npcv {

	typedef unsigned char uchar;

	/**
	 * @class	Image
	 *
	 * @brief	An image.
	 * @todo Make new cstors with optional arg for copy or point to pixels data
	 */
	class Image
	{
	public:
		Image();
		Image(Image* image);
		Image(int width, int height, PixelType type);
		Image(uchar* data, int width, int height, PixelType type);
		~Image();

		/** @brief	The pixels components array. */
		uchar* pixels;
		/** @brief	Image width. */
		int width;
		/** @brief	Image height. */
		int height;

		/** @brief	Image color type. */
		PixelType type;

		std::function<void(Image*)> freeDataFunc;

		/**
		 * @brief	Get pixel at coordinate.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 *
		 * @return	null if it fails, else a pointer to a Pixel.
		 */
		Pixel* pixel(int x, int y);

		//void pixelSet(int x, int y, Pixel* value);

		/**
		 * @brief	Loads image file from memory.
		 *
		 * @param [in,out]	fileMem	Pointer to memory.
		 * @param	bytes		   	Size in bytes.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool loadFromMemory(unsigned char* fileMem, size_t size);

		/**
		 * @brief	Gets sub image.
		 *
		 * @param	x	  	The x coordinate.
		 * @param	y	  	The y coordinate.
		 * @param	width 	The width.
		 * @param	height	The height.
		 *
		 * @return	null if it fails, else the sub image.
		 */
		Image* getSubImage(int x, int y, int width, int height);

		/**
		 * @brief	Saves to file via shared ImageStream.
		 *
		 * @param	filepath	The filepath.
		 *
		 * @return	true if it succeeds, false if it fails.
		 */
		bool saveToFile(std::string filepath);

		/**
		 * @brief	Converts this image to a grayscale.
		 *
		 * @return	true if it succeeds, false if it fails.
		 * @todo Find better place for this.
		 */
		bool convertToGrayscale();



//		foreachPixel( [](Pixel* pixel) {
//		});
		void foreachPixel(std::function<void(Pixel*)> iterFunction);

		/**
		 * @brief	Set all pixels color.
		 *
		 * @param	r	The int to process.
		 * @param	g	The int to process.
		 * @param	b	The int to process.
		 *
		 * @return	true if it succeeds, false if it fails.
		 * @todo Make variant with Pixel* argument
		 */
		bool setColor(int r, int g, int b);

		/**
		 * @fn	Image Image::operator+(Image image)
		 *
		 * @brief	Addition operator. Allocate new image
		 *
		 * @param	image	The image.
		 *
		 * @return	The result of the operation.
		 */
		Image operator+(Image image) {
			Image ret = Image(width, height, type);
			for_each_pixel(this)
				Pixel* px2 = image.pixel(x, y);
				Pixel np = (*px2 + *pixel);
				ret.pixel(x, y)->setColor(&np);
				delete px2;
			for_each_pixel_end
			return ret;
		}

		/**
		 * @fn	void Image::operator+=(Image image)
		 *
		 * @brief	Addition assignment operator.
		 *
		 * @param	image	The image.
		 */
		void operator+=(Image image) {
			for_each_pixel(this)
				Pixel* px2 = image.pixel(x, y);
				*pixel += *px2;
				delete px2;
			for_each_pixel_end
		}
		/**
		 * @fn	void Image::operator-=(Image image)
		 *
		 * @brief	Subtraction assignment operator.
		 *
		 * @param	image	The image.
		 */
		void operator-=(Image image) {
			for_each_pixel(this)
				Pixel* px2 = image.pixel(x, y);
				*pixel -= *px2;
			for_each_pixel_end
		}
		/**
		 * @fn	Image Image::operator-(Image image)
		 *
		 * @brief	Subtraction operator. Allocate new image
		 *
		 * @param	image	The image.
		 *
		 * @return	The result of the operation.
		 */
		Image operator-(Image image) {
			Image ret = Image(width, height, type);
			for_each_pixel(this)
				Pixel* px2 = image.pixel(x, y);
				Pixel np = *pixel - *px2;
				ret.pixel(x, y)->setColor(&np);
			delete px2;
			for_each_pixel_end
			return ret;
		}
	protected:

		/**
		 * @brief	Get pointer to first component for target pixel.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 *
		 * @return	null if it fails, else a pointer to an uchar.
		 */
		uchar* pixel_ptr(int x, int y);

		/**
		 * @brief	Set pointer to first component for target pixel.
		 *
		 * @param	x					The x coordinate.
		 * @param	y					The y coordinate.
		 * @param [in,out]	colorPtr	If non-null, the color pointer.
		 */
		void pixelSet_ptr(int x, int y, uchar* colorPtr);
	};

}

