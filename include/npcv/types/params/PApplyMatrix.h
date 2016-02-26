#pragma once

namespace npcv {namespace types {

	class PApplyMatrix {
	public:
		PApplyMatrix(int mWidth, int mHeight, float bias, float factor, float* matrix);
		~PApplyMatrix();

	};



	}
}