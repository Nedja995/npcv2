/*
* Copyright (c) 2016 Nedeljko Pejasinovic (nedjaunity@gmail.com)
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#pragma once

#include "npcv/utils/SamplingImage.h"

namespace npcv { namespace utils {

	SamplingImage::SamplingImage(Image * image) : _image(image)
	{
	}

	SamplingImage::~SamplingImage()
	{
	}

	vector<Image*> SamplingImage::Subimages(int width, int height)
	{
		vector<Image*> ret = vector<Image*>();
		Image* subImage = 0;

		for (int x = 0; x < _image->width - width; x += width)
		{
			for (int y = 0; y < _image->height; y += height)
			{
				subImage = &_image->getSubImage(x, y, width, height);
				ret.push_back(subImage);
			}
		}

		return ret;
	}
}
}