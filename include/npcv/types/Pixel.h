
#include <algorithm>

#define R(pixel) *(pixel->firstComp )
#define G(pixel) *(pixel->firstComp + 1)
#define B(pixel) *(pixel->firstComp + 2)

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
		Pixel(uchar* firstComp, PixelType type) : firstComp(firstComp), type(type) {};
		Pixel(Pixel* pixel, bool copy);
		PixelType type;
		uchar* firstComp;
		int color[];

		int& operator[] (int i) {
			return color[i];
		}

		//bool setColor(int color[]);

		Pixel operator+(Pixel px) {
			Pixel ret = Pixel(px);
			//R((&ret)) = std::max(std::min(R(this) + R((&px)), 255), 0);
			//G((&ret)) = std::max(std::min(G(this) + G((&px)), 255), 0);
			//B((&ret)) = std::max(std::min(B(this) + B((&px)), 255), 0);
			int r = R(this);
			int g = G(this);
			int b = B(this);
			r += R((&px));
			g += G((&px));
			b += B((&px));
			r = std::max(std::min(r, 255), 0);
			g = std::max(std::min(g, 255), 0);
			b = std::max(std::min(b, 255), 0);
			R((&ret)) = r;
			G((&ret)) = g;
			B((&ret)) = b;
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

		Pixel operator-(Pixel px) {
			int r1 = R((&px));
			int g1 = G((&px));
			int b1 = B((&px));
			int r2 = R(this);
			int g2 = G(this);
			int b2 = B(this);
			Pixel ret = Pixel(px);
			int rN = r1 - r2;
			int gN = g1 - g2;
			int bN = b1 - b2;
			rN = (rN > 255) ? 255 : rN;
			rN = (rN < 0) ? 0 : rN;
			gN = (gN > 255) ? 255 : gN;
			gN = (gN < 0) ? 0 : gN;
			bN = (bN > 255) ? 255 : bN;
			bN = (bN < 0) ? 0 : bN;
			R((&ret)) = 255 - rN;
			G((&ret)) = 255 - gN;
			B((&ret)) = 255 - bN;
			return ret;
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