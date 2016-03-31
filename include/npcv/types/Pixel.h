
#include <algorithm>

#define R(pixel) *(pixel->colorPtr )
#define G(pixel) *(pixel->colorPtr + 1)
#define B(pixel) *(pixel->colorPtr + 2)

namespace npcv {

	typedef unsigned char uchar;

	enum PixelType {
		Null = 0,
		GRAY = 1,
		GA = 2,
		RGB = 3,
		RGBA = 4
	};


	class Pixel {
	public:

		static Pixel& Null();

		Pixel();
		Pixel(uchar* colorPtr, PixelType type) : colorPtr(colorPtr), type(type), _allocated(false){};
		Pixel(Pixel* pixel, bool copy);
		~Pixel();
		PixelType type;
		uchar* colorPtr;
		bool isPointer();

		int color(int index);

		bool setColor(int r, int g, int b);

		bool setColor(Pixel* pixel);

		/**
		 * @fn	bool Pixel::setColor(int g);
		 *
		 * @brief	Sets a color.
		 *
		 * @param	g	Gray value.
		 *
		 * @return	true if image type is GRAY.
		 */
		bool setColor(int g);

		/**
		 * @fn	Pixel Pixel::operator+(Pixel px)
		 *
		 * @brief	Addition operator.
		 *
		 * @param	px	The pixel.
		 *
		 * @return	The result of the operation.
		 */
		Pixel operator+(Pixel px) {
			Pixel ret = Pixel(&px, true);
			R((&ret)) = std::max(std::min(R(this) + R((&px)), 255), 0);
			G((&ret)) = std::max(std::min(G(this) + G((&px)), 255), 0);
			B((&ret)) = std::max(std::min(B(this) + B((&px)), 255), 0);
			return ret;
		}
		/**
		 * @fn	Pixel Pixel::operator-(Pixel px)
		 *
		 * @brief	Subtraction operator.
		 *
		 * @param	px	The pixel.
		 *
		 * @return	The result of the operation.
		 */
		Pixel operator-(Pixel px) {
			Pixel ret = Pixel(&px, true);
			R((&ret)) = std::max(std::min(R(this) - R((&px)), 255), 0);
			G((&ret)) = std::max(std::min(G(this) - G((&px)), 255), 0);
			B((&ret)) = std::max(std::min(B(this) - B((&px)), 255), 0);
			return ret;
		}
		/**
		 * @fn	void Pixel::operator+=(Pixel px)
		 *
		 * @brief	Addition assignment operator.
		 *
		 * @param	px	The pixel.
		 */
		void operator+=(Pixel px) {
			R(this) = std::max(std::min(R((&px)) + R(this), 255), 0);
			G(this) = std::max(std::min(G((&px)) + G(this), 255), 0);
			B(this) = std::max(std::min(B((&px)) + B(this), 255), 0);
		}
		/**
		 * @fn	void Pixel::operator-=(Pixel px)
		 *
		 * @brief	Subtraction assignment operator.
		 *
		 * @param	px	The pixel.
		 */
		void operator-=(Pixel px) {
			R(this) = std::max(std::min(R(this) - R((&px)), 255), 0);
			G(this) = std::max(std::min(G(this) - G((&px)), 255), 0);
			B(this) = std::max(std::min(B(this) - B((&px)), 255), 0);
		}
	protected:
		/** @brief	Is allocated memory on creation or point to image pixels array. */
		bool _allocated;
		/**
		* @brief	Check is component number equal.
		*
		* @param	target	 	Target type.
		*
		* @return	true if image type same.
		*/
		bool _assertTypeStrict(PixelType target);
		/**
		* @brief	Check is component number equal or greater.
		*
		* @param	target	 	Target type.
		*
		* @return	true if image type same.
		*/
		bool _assertType(PixelType target );

	};
}