
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

		//static Pixel& Create();
		//static Pixel& Create(Pixel& pixel);
		static Pixel& Create(PixelType type);
		static Pixel& Create(uchar* components, PixelType type);
		static Pixel& Create(uchar* components, PixelType type, bool isPointer);
		static Pixel& Create(int g);
		static Pixel& Create(int r, int g, int b);

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

		bool setColor(Pixel& pixel);

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
		Pixel& operator*(Pixel& px) {
			Pixel& ret = Pixel::Create(this->colorPtr, this->type);
			if (ret.type == GRAY) {
				int mulVal = *(ret.colorPtr) * *(ret.colorPtr);
				*(ret.colorPtr) = std::max(std::min(mulVal, 255), 0);
			}
			else if (ret.type == RGB) {

			}
			return ret;
		}

		/**
		* @fn	Pixel Pixel::operator+(Pixel px)
		*
		* @brief	Addition operator.
		*
		* @param	px	The pixel.
		*
		* @return	The result of the operation.
		*/
		Pixel& operator*(int val) {
			Pixel& ret = Pixel::Create(this->colorPtr, this->type);
			if (ret.type == GRAY) {
				int mulVal = *(ret.colorPtr) * val;
				*(ret.colorPtr) = std::max(std::min(mulVal, 255), 0);
			}
			else if (ret.type == RGB) {

			}
			return ret;
		}

		/**
		* @fn	Pixel Pixel::operator+(Pixel px)
		*
		* @brief	Addition operator.
		*
		* @param	px	The pixel.
		*
		* @return	The result of the operation.
		*/
		Pixel& operator/(int val) {
			Pixel& ret = Pixel::Create(this->colorPtr, this->type);
			if (ret.type == GRAY) {
				int divVal = *(ret.colorPtr) / val;
				*(ret.colorPtr) = std::max(std::min(divVal, 255), 0);
			}
			else if (ret.type == RGB) {

			}
			return ret;
		}

		/**
		 * @fn	Pixel Pixel::operator+(Pixel px)
		 *
		 * @brief	Addition operator.
		 *
		 * @param	px	The pixel.
		 *
		 * @return	The result of the operation.
		 */
		Pixel& operator+(Pixel& px) {
			Pixel& ret = Pixel::Create(px.type);
			ret.setColor(
				std::max(std::min(R(this) + R((&px)), 255), 0),
				std::max(std::min(G(this) + G((&px)), 255), 0),
				std::max(std::min(B(this) + B((&px)), 255), 0));
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
		Pixel& operator-(Pixel& px) {
			Pixel& ret = Pixel::Create(px.type);
			ret.setColor(
				std::max(std::min(R(this) - R((&px)), 255), 0),
				std::max(std::min(G(this) - G((&px)), 255), 0),
				std::max(std::min(B(this) - B((&px)), 255), 0));
			return ret;
		}
		/**
		 * @fn	void Pixel::operator+=(Pixel px)
		 *
		 * @brief	Addition assignment operator.
		 *
		 * @param	px	The pixel.
		 */
		void operator+=(Pixel& px) {
			setColor(
				std::max(std::min(R(this) + R((&px)), 255), 0),
				std::max(std::min(G(this) + G((&px)), 255), 0),
				std::max(std::min(B(this) + B((&px)), 255), 0));
		}
		/**
		 * @fn	void Pixel::operator-=(Pixel px)
		 *
		 * @brief	Subtraction assignment operator.
		 *
		 * @param	px	The pixel.
		 */
		void operator-=(Pixel& px) {
			setColor(
				std::max(std::min(R(this) - R((&px)), 255), 0),
				std::max(std::min(G(this) - G((&px)), 255), 0),
				std::max(std::min(B(this) - B((&px)), 255), 0));
		}

		bool operator==(Pixel& px) {
			if (type == GRAY) {
				if (px.color(0) == color(0)) {
					return true;
				}
			}
			return false;
		}

		bool operator!=(Pixel& px) {
			if (type == GRAY) {
				if (px.color(0) == color(0)) {
					return false;
				}
			}
			return true;
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