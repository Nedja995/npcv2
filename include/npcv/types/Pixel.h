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
		PixelType type;
		uchar* firstComp;
		int color[];

		int& operator[] (int i) {
			return color[i];
		}

		Pixel operator+(Pixel px) {
			int r1 = px[0];
			int g1 = px[1];
			int b1 = px[2];
			int r2 = color[0];
			int g2 = color[1];
			int b2 = color[2];
			Pixel ret = Pixel(px);
			int rN = r1 + r2;
			int gN = g1 + g2;
			int bN = b1 + b2;
			rN = (rN > 255) ? 255 : rN;
			rN = (rN < 0) ? 0 : rN;
			gN = (gN > 255) ? 255 : gN;
			gN = (gN < 0) ? 0 : gN;
			bN = (bN > 255) ? 255 : bN;
			bN = (bN < 0) ? 0 : bN;
			ret[0] = 255 - rN;
			ret[1] = 255 - gN;
			ret[2] = 255 - bN;
			return ret;
		}

		Pixel operator-(Pixel px) {
			int r1 = px[0];
			int g1 = px[1];
			int b1 = px[2];
			int r2 = color[0];
			int g2 = color[1];
			int b2 = color[2];
			Pixel ret = Pixel(px);
			int rN = r1 + r2;
			int gN = g1 + g2;
			int bN = b1 + b2;
			rN = (rN > 255) ? 255 : rN;
			rN = (rN < 0) ? 0 : rN;
			gN = (gN > 255) ? 255 : gN;
			gN = (gN < 0) ? 0 : gN;
			bN = (bN > 255) ? 255 : bN;
			bN = (bN < 0) ? 0 : bN;
			ret[0] = 255 - rN;
			ret[1] = 255 - gN;
			ret[2] = 255 - bN;
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