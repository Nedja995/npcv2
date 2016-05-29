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
#include <string>
#include "npcv/filters/IProcessImage.h"
#include <map>
namespace npcv{ namespace converters{ 
	using namespace processing;
	using namespace std;

	class NPipeRequestToImageProcess {
	public:
		NPipeRequestToImageProcess(unsigned char* message, unsigned long lenght);
		~NPipeRequestToImageProcess();
		bool parse();
		bool isParsed();
		std::string getProcessName();
		IProcessImage* getProcess();
	protected:
		IProcessImage* _makeApplyMatrixProc(map<string, void*> params);
		unsigned char* _message;
		unsigned long _msgLenght;
		Image* _imageRecived;
		IProcessImage* _process;
		
		////////////////////////////
		// Parsers functions
		

		/**
		* \brief Parse string betwen first brace pair
		* \param char* text
		* \param string Value betwen brace pair 
		*/
		std::string _parseBraces(char* text);

		map<string, void*> _parseParamMatrix(std::string params);

	};


} }