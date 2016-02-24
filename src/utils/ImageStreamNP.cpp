#include "npcv/utils/ImageStreamNP.h"
#include <windows.h>
#include <iostream>

#include "thirdparty/stb/stb_image.h"
#include "thirdparty/stb/stb_image_write.h"

#include "npcv/processes/IPMatrixApply.h"

extern unsigned char *stbi_write_png_to_mem(unsigned char *pixels, int stride_bytes, int x, int y, int n, int *out_len);

namespace npcv
{
	using namespace npcv;
	using namespace processing;
	void __cleanUp(HANDLE hPipe);


	ImageStreamNP * ImageStreamNP::Create()
	{
		ImageStreamNP * ret = new ImageStreamNP();
		ret->_serverName = ".";
		ret->_pipeName = "SamplePipe";
		ret->_fullPipeName = "\\\\" 
							+ ret->_serverName 
							+ "\\pipe\\" 
							+ ret->_pipeName;
		return ret;
	}
	Image * ImageStreamNP::Load(std::string path)
	{
		_openWinNamedPipe();
		return nullptr;
	}
	bool ImageStreamNP::Save(Image * image, std::string path)
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
			  // Receive a response from server.
			  // 
			unsigned char charsRecived[_bufferSize];
			unsigned long bytesCountRecived, bytesCountReaded;
			bytesCountRecived = sizeof(charsRecived);
			BOOL fFinishRead = FALSE;
			do {

				fFinishRead = ReadFile(
					hPipe,                  // Handle of the pipe
					charsRecived,           // Buffer to receive the reply
					bytesCountRecived,      // Size of buffer in bytes
					&bytesCountReaded,		// Number of bytes read 
					NULL                    // Not overlapped 
					);

				if (!fFinishRead && ERROR_MORE_DATA != GetLastError())
				{
					dwError = GetLastError();
					std::cout << "ReadFile from pipe failed w/err " << dwError << std::endl;
					__cleanUp(hPipe);
				}

				//std::wstring wstr(charsRecived);
				//std::string recivedStr(wstr.begin(), wstr.end());

				std::cout << "Receive " << bytesCountReaded << " bytes from server: " << charsRecived << std::endl;

			} while (!fFinishRead); // Repeat loop if ERROR_MORE_DATA


			Image* recivedImage = new Image();
			recivedImage->loadFromMemory(charsRecived, bytesCountReaded);

			///////////////////////////////////////////////
			//PROCESS
			IPMatrixApply* matrixProc = new IPMatrixApply();
			//configure process
			matrixProc->setImage(recivedImage);
			int matrixSize = 3;

			matrixProc->matrixSize = matrixSize;
			float filter[9] =
			{
				1, 0, 1,
				-2, 0, 2,
				-1, 0, 1
			};
			matrixProc->matrix = &filter[0];
			/*matrixProc->bias = ;
			matrixProc->factor = ;*/
			matrixProc->initialize();
			matrixProc->execute();

			//free
			matrixProc->free();
			delete matrixProc;


			///////////////////////////////


			stbi_write_png("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\transfer.png", recivedImage->width, recivedImage->height, recivedImage->type, recivedImage->pixels, 0);

			// 
			// Send a request from client(this) to server
			// 
			//load image with stb
			int width, height, type;
			//unsigned char* data = stbi_load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\photo3.bmp", &width, &height, &type, 3);
			int len;
			unsigned char *png = stbi_write_png_to_mem((unsigned char *)recivedImage->pixels, 0, recivedImage->width, recivedImage->height, recivedImage->type, &len);

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