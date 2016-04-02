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
	for(int x = 0; x < image.width; x++) { \
	for(int y = 0; y < image.height; y++) { \
		Pixel& pixel = image.pixel(x, y, true);
 /**
 * @def	for_each_pixel_end	delete pixel;}}
 *
 * @brief	End macro for iterating over image pixels.
 */
#define for_each_pixel_end	delete &pixel;}}

namespace npcv {
	/** @brief Pixel component value */
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
		/*************************************************
		/*  CONSTRUCTORS
		**************************************************/
		/**
		 * @fn	static Image& Image::Create();
		 *
		 * @brief	Creates a new Image&amp;
		 *
		 * @return	A reference to an Image.
		 */
		static Image& Create();
		/**
		 * @brief	Creates a new Image&amp;
		 *
		 * @param	width 	The width.
		 * @param	height	The height.
		 * @param	type  	The type.
		 *
		 * @return	A reference to an Image.
		 */
		static Image& Create(int width, int height, PixelType type);
		/**
		 * @brief	Creates a new Image&amp;
		 *
		 * @param	width		  	The width.
		 * @param	height		  	The height.
		 * @param	type		  	The type.
		 * @param [in,out]	pixels	If non-null, the pixels.
		 *
		 * @return	A reference to an Image.
		 */
		static Image& Create(int width, int height, PixelType type, uchar* pixels);
		/**
		 * @brief	Creates a new Image that point to pixels allocated in other place;
		 *
		 * @param [in,out]	image	The image to point at their pixels.
		 *
		 * @return	A reference to an new Image.
		 */
		static Image& Create(Image& image);
		/**
		* @brief	Creates a empty Image;
		*
		* @return	A reference to an new Image.
		*/
		static Image& Null();

		Image();
		Image(Image& image);
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
		 * @brief	Memory size.
		 *
		 * @return	Size in bytes.
		 */
		inline size_t memSize();

		/**
		 * @brief	Get pixel at coordinate.
		 *
		 * @param	x	The x coordinate.
		 * @param	y	The y coordinate.
		 *
		 * @return	null if it fails, else a pointer to a Pixel.
		 */
		Pixel& pixel(int x, int y);

		Pixel& pixel(int x, int y, bool isPointer);

		void setPixel(int x, int y, Pixel& pixel);

	//	void setPixel(int x, int y, int g);

		
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
		 * @brief	Sets pixels copy.
		 *
		 * @param [in,out]	image	The image which pixels to copy.
		 *
		 * @return	true if it succeeds, false if it fails.
		 * @todo Implement image check
		 */
		bool setPixelsCopy(Image& image);

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

		void foreachPixel(std::function<void(Pixel&)> iterFunction);
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
		Image& operator+(Image& image) {
			Image& ret = Image::Create(width, height, type);
			for_each_pixel((*this))
				Pixel& px2 = image.pixel(x, y);		
				Pixel& np = pixel + px2;
				ret.setPixel(x, y, np);
				delete &px2;
				delete &np;
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
		void operator+=(Image& image) {
			for_each_pixel((*this))
				Pixel& px2 = image.pixel(x, y);
				pixel += px2;
				delete &px2;
			for_each_pixel_end
		}
		/**
		 * @fn	void Image::operator-=(Image image)
		 *
		 * @brief	Subtraction assignment operator.
		 *
		 * @param	image	The image.
		 */
		void operator-=(Image& image) {
			for_each_pixel((*this))
				Pixel& px2 = image.pixel(x, y);
				pixel -= px2;
				delete &px2;
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
		Image& operator-(Image& image) {
			Image& ret = Image::Create(width, height, type);
			for_each_pixel((*this))
				Pixel& px2 = image.pixel(x, y);
			Pixel& np = pixel - px2;
			ret.setPixel(x, y, np);
			delete &px2;
			delete &np;
			for_each_pixel_end
				return ret;
		}
	protected:
		bool _allocatedPixels;
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

