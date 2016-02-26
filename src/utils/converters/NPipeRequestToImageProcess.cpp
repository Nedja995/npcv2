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

#include "npcv/utils/converters/NPipeRequestToImageProcess.h"
#include "npcv/processes/IPMatrixApply.h"
#include <iostream>
#include <vector>
#include <sstream>

namespace npcv { namespace converters {

	NPipeRequestToImageProcess::NPipeRequestToImageProcess(unsigned char * message, unsigned long lenght)
		: _message(message)
		, _msgLenght(lenght)
	{
	}

	NPipeRequestToImageProcess::~NPipeRequestToImageProcess()
	{
	}

	bool NPipeRequestToImageProcess::parse()
	{

		//////////////////////////////////////////
		// PARSE REQUEST

		// check is valid - read first 8 char to find "REQUEST" string
		int offset = 0;
		std::string str = std::string((char*)_message, sizeof(char) * 8);
		offset += 8;			// "REQUEST:"
		if (str == "REQUEST:") {
			string processName = _parseBraces((char*)_message + 8);
			string params = "";
			unsigned char* imageFileData = 0;
			if (processName == "matrix") {
				offset += 6;	// "{matrix}"
				offset += 9;	// "_PARAMS:{"
				params = _parseBraces((char*)_message + offset + 1);// parse params string
				offset += params.length(); // "{mWidth,mHeight,bias,factor,m0.0f,m0.1f,m1.0f,.."}
				imageFileData = _message + offset + 3; // ".}" logic bug
				//make image from bytes
				_imageRecived = new Image(); 
				size_t imageDataLenght = _msgLenght - offset * sizeof(char);
				_imageRecived->loadFromMemory(imageFileData, imageDataLenght);
				//parse params
				map<string, void*> paramsMap = _parseParamMatrix(params);

				_process = _makeApplyMatrixProc(paramsMap);
			}
		}
		else {
			std::cout << "npcv:ImageStreamNP: bad request recived from server" << std::endl;
			return false;
		}
		return true;
	}

	bool NPipeRequestToImageProcess::isParsed()
	{
		if (_message == 0) {
			return false;
		}
		if (_imageRecived == 0) {
			return false;
		}
		if (_process == 0) {
			return false;
		}
		return true;
	}

	std::string NPipeRequestToImageProcess::getProcessName()
	{
		return std::string();
	}

	IProcessImage * NPipeRequestToImageProcess::getProcess()
	{
		return _process;
	}

	IProcessImage * NPipeRequestToImageProcess::_makeApplyMatrixProc(map<string, void*> params)
	{
		int mWidth = (int)params["mWidth"];
		int mHeight = (int)params["mHeight"];
		float bias = *(float*)params["bias"];
		float factor = *(float*)params["factor"];
		float* matrix = (float*)params["matrix"];
		/////////////////////////////////////////////////
		////PROCESS
		IPMatrixApply* matrixProc = new IPMatrixApply();
		//configure process
		matrixProc->setImage(_imageRecived);
		matrixProc->matrixSize = mWidth;
		matrixProc->matrix = matrix;
		matrixProc->bias = bias;
		matrixProc->factor = factor;
		matrixProc->initialize();
		///////////////////////////////
		return matrixProc;
	}

	std::string NPipeRequestToImageProcess::_parseBraces(char * text)
	{
		std::string ret = "";
		bool start = false, end = false;
		for (int i = 0; !end; i++) {
			if		(*(text + i) == '{')	start = true;
			else if (*(text + i) == '}')	end = true;
			else							ret += *(text + i);
		}
		return ret;
	}
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}


	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}
	
	// 
	// TODO: MEMORY LEAK
	//
	map<string, void*> NPipeRequestToImageProcess::_parseParamMatrix(std::string params)
	{
		map<string, void*> ret = map<string, void*>();
		int mWidth, mHeight;
		float bias, factor;
		float* matrix;

		vector<string> pTokens = split(params, ',');
		mWidth = stoi(pTokens[0].c_str());
		mHeight = stoi(pTokens[1].c_str());
		bias = stof(pTokens[2].c_str());
		factor = stof(pTokens[3].c_str());

		//matrix copy
		int mLen = mWidth * mHeight;
		matrix = new float[mLen];
		for (int i = 4; i < pTokens.size(); i++) {
			matrix[i - 4] = stof(pTokens[i].c_str());
		}



		ret["mWidth"] = (void*)mWidth;
		ret["mHeight"] = (void*)mHeight;
		float* biasPtr = (float*)malloc(sizeof(float));
		memcpy(biasPtr, &bias, sizeof(float));
		ret["bias"] = (void*)biasPtr;
		float* factorPtr = (float*)malloc(sizeof(float));
		memcpy(factorPtr, &factor, sizeof(float));
		ret["factor"] = (void*)factorPtr;
		ret["matrix"] = (void*)matrix;

		return ret;
	}
	

}
}