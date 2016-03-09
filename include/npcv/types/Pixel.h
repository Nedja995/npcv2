
#include <algorithm>

#define R(pixel) *(pixel->colorPtr )
#define G(pixel) *(pixel->colorPtr + 1)
#define B(pixel) *(pixel->colorPtr + 2)

namespace npcv {

	typedef unsigned char uchar;

	enum PixelType {
		GRAY = 1,
		GA = 2,
		RGB = 3,
		RGBA = 4
	};


	class Pixel {
	public:
		Pixel(uchar* colorPtr, PixelType type) : colorPtr(colorPtr), type(type), allocated(false){};
		Pixel(Pixel* pixel, bool copy);
		~Pixel();
		PixelType type;
		uchar* colorPtr;
		bool allocated;
		int color[];

		int& operator[] (int i) {
			return color[i];
		}

		//bool setColor(int color[]);

		Pixel operator+(Pixel px) {
			Pixel ret = Pixel(&px, true);
			R((&ret)) = std::max(std::min(R(this) + R((&px)), 255), 0);
			G((&ret)) = std::max(std::min(G(this) + G((&px)), 255), 0);
			B((&ret)) = std::max(std::min(B(this) + B((&px)), 255), 0);
			return ret;
		}

		Pixel operator-(Pixel px) {
			Pixel ret = Pixel(&px, true);
			R((&ret)) = std::max(std::min(R(this) - R((&px)), 255), 0);
			G((&ret)) = std::max(std::min(G(this) - G((&px)), 255), 0);
			B((&ret)) = std::max(std::min(B(this) - B((&px)), 255), 0);
			return ret;
		}

		void operator+=(Pixel px) {
			R(this) = std::max(std::min(R((&px)) + R(this), 255), 0);
			G(this) = std::max(std::min(G((&px)) + G(this), 255), 0);
			B(this) = std::max(std::min(B((&px)) + B(this), 255), 0);
		}

		void operator-=(Pixel px) {
			R(this) = std::max(std::min(R(this) - R((&px)), 255), 0);
			G(this) = std::max(std::min(G(this) - G((&px)), 255), 0);
			B(this) = std::max(std::min(B(this) - B((&px)), 255), 0);
		}

		Pixel operator*(float value) {
			Pixel ret = Pixel(*this);
			int rN = color[0] * value;
			int gN = color[1] * value;
			int bN = color[2] * value;
			rN = (rN > 255) ? 255 : rN;
			rN = (rN < 0) ? 0 : rN;
			gN = (gN > 255) ? 255 : gN;
			gN = (gN < 0) ? 0 : gN;
			bN = (bN > 255) ? 255 : bN;
			bN = (bN < 0) ? 0 : bN;
			color[0] = rN;
			color[1] = gN;
			color[2] = bN;
			return ret;
		}

		Pixel operator*=(Pixel value) {
			Pixel ret = Pixel(*this);
			int rN = color[0] * value[0];
			int gN = color[1] * value[1];
			int bN = color[2] * value[2];
			rN = (rN > 255) ? 255 : rN;
			rN = (rN < 0) ? 0 : rN;
			gN = (gN > 255) ? 255 : gN;
			gN = (gN < 0) ? 0 : gN;
			bN = (bN > 255) ? 255 : bN;
			bN = (bN < 0) ? 0 : bN;
			color[0] = rN;
			color[1] = gN;
			color[2] = bN;
			return ret;
		}
	};
}