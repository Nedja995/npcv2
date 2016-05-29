#include "npcv/utils/ImageStreamNP.h"
#include <windows.h>
#include <iostream>
#include <string>

#include "thirdparty/stb/stb_image.h"
#include "thirdparty/stb/stb_image_write.h"

#include "npcv/utils/converters/NPipeRequestToImageProcess.h"

extern unsigned char *stbi_write_png_to_mem(unsigned char *pixels, int stride_bytes, int x, int y, int n, int *out_len);

namespace npcv
{
	using namespace std;
	//using namespace npcv;
//	using namespace processing;
	using namespace converters;
	void __cleanUp(HANDLE hPipe);


	ImageStreamNP * ImageStreamNP::Create()
	{
		ImageStreamNP * ret = new ImageStreamNP();
		ret->_serverName = ".";
		ret->_pipeName = "NpcvPipe";
		ret->_fullPipeName = "\\\\" 
							+ ret->_serverName 
							+ "\\pipe\\" 
							+ ret->_pipeName;
		return ret;
	}

	Image& ImageStreamNP::Load(std::string path)
	{
		_openWinNamedPipe();
		return Image::Null();
	}

	bool ImageStreamNP::Save(Image& image, std::string path)
	{
		return false;
	}

	void ImageStreamNP::free()
	{
	}

	unsigned long ImageStreamNP::_openWinNamedPipe()
	{
		HANDLE hPipe = INVALID_HANDLE_VALUE;
		DWORD dwError = ERROR_SUCCESS;

		while (true) {

			// Wait for connection to server
			while (true)
			{
				hPipe = CreateFile(
					_fullPipeName.c_str(),          // Pipe name 
					GENERIC_READ | GENERIC_WRITE,   // Read and write access
					0,                              // No sharing 
					NULL,                           // Default security attributes
					OPEN_EXISTING,                  // Opens existing pipe
					0,                              // Default attributes
					NULL                            // No template file
					);

				// If pipe opened - break while
				if (hPipe != INVALID_HANDLE_VALUE)
				{
					std::cout << "npcv: The named pipe " << _fullPipeName << " is connected.";
					break;
				}
				//get errror
				dwError = GetLastError();

				// Errors that is not ERROR_PIPE_BUSY
				if (ERROR_PIPE_BUSY != dwError)
				{
					//	std::cerr << "npcv:ImageStreamNP: Unable to open named pipe w/err " << dwError;
					__cleanUp(hPipe);
				}

				// All pipe instances are busy, so wait for 5 seconds.
				if (!WaitNamedPipe(_fullPipeName.c_str(), 5000))
				{
					dwError = GetLastError();
					//	std::cerr << "npcv:ImageStreamNP: Could not open pipe. 5 second wait timed out.";
					__cleanUp(hPipe);
				}
			} //End while

			//
			// RECIVE a response from server.
			// 
			unsigned char charsRecived[950000];
			unsigned long bytesCountRecived, bytesCountReaded;
			bytesCountRecived = sizeof(charsRecived);
			BOOL fFinishRead = FALSE;
			do 
			{
				// Read
				fFinishRead = ReadFile(
					hPipe,                  // Handle of the pipe
					charsRecived,           // Buffer to receive the reply
					bytesCountRecived,      // Size of buffer in bytes
					&bytesCountReaded,		// Number of bytes read 
					NULL                    // Not overlapped 
					);

				//check error
				if (!fFinishRead && ERROR_MORE_DATA != GetLastError())
				{
					dwError = GetLastError();
					std::cout << "ReadFile from pipe failed because: " << dwError << std::endl;
					__cleanUp(hPipe); //cleanup pipe
				}
				//log
				std::cout << "Receive " << bytesCountReaded << " bytes from server: " << charsRecived << std::endl;
			//
			// Repeat loop if ERROR_MORE_DATA
			} while (!fFinishRead); 

			IProcessImage* imageProcessing = 0;
			NPipeRequestToImageProcess* reqestConverter = new NPipeRequestToImageProcess(charsRecived, bytesCountReaded);
			if (!reqestConverter->parse()) {
				cout << "npcv:ImageStreamNP: FAILED pasing request to image process" << endl;
			}
			else {
				imageProcessing = reqestConverter->getProcess();
			}
			
			imageProcessing->execute();

			// 
			// SEND a request from client(this) to server
			// 
			//load image with stb
			int width, height, type;
			//unsigned char* data = stbi_load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\photo3.bmp", &width, &height, &type, 3);
			int len;
			unsigned char *png = stbi_write_png_to_mem((unsigned char *)imageProcessing->getImage()->pixels, 0, imageProcessing->getImage()->width, imageProcessing->getImage()->height, imageProcessing->getImage()->type, &len);

			DWORD bytesCountWritten;

			if (!WriteFile(
				hPipe,              // Handle of the pipe
				png,                // Message to be written
				len,                // Number of bytes to write
				&bytesCountWritten,      // Number of bytes written
				NULL))				// Not overlapped
			{
				dwError = GetLastError();
				std::cerr << "npcv:ImageStreamNP: WriteFile to pipe failed w/err" << dwError;
				__cleanUp(hPipe);
			}

			std::cout << "Send " << bytesCountWritten << " bytes " << std::endl;
		
			//free pipe
			__cleanUp(hPipe);
		}
		return dwError;
	}

	void __cleanUp(HANDLE hPipe)
	{
		// Centralized cleanup for all allocated resources.
		if (hPipe != INVALID_HANDLE_VALUE)
		{
			CloseHandle(hPipe);
			hPipe = INVALID_HANDLE_VALUE;
		}
	}


}