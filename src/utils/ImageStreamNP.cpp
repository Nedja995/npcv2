#include "npcv/utils/ImageStreamNP.h"
#include <windows.h>
#include <iostream>

#include "thirdparty/stb/stb_image.h"
#include "thirdparty/stb/stb_image_write.h"

extern unsigned char *stbi_write_png_to_mem(unsigned char *pixels, int stride_bytes, int x, int y, int n, int *out_len);

namespace npcv
{
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
	Image * ImageStreamNP::Load(const char * path)
	{
		_openWinNamedPipe();
		return nullptr;
	}
	bool ImageStreamNP::Save(Image * image, const char * path)
	{
		return false;
	}
	void ImageStreamNP::free()
	{
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


	unsigned long ImageStreamNP::_openWinNamedPipe()
	{
		HANDLE hPipe = INVALID_HANDLE_VALUE;
		DWORD dwError = ERROR_SUCCESS;

		// Try to open the named pipe identified by the pipe name.
		while (TRUE)
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

			// If the pipe handle is opened successfully ...
			if (hPipe != INVALID_HANDLE_VALUE)
			{
				std::cout << L"The named pipe " << _fullPipeName << " is connected.";
				break;
			}

			dwError = GetLastError();

			// Exit if an error other than ERROR_PIPE_BUSY occurs.
			if (ERROR_PIPE_BUSY != dwError)
			{
				std::cerr << "Unable to open named pipe w/err " << dwError;
				__cleanUp(hPipe);
			}

			// All pipe instances are busy, so wait for 5 seconds.
			if (!WaitNamedPipe(_fullPipeName.c_str(), 5000))
			{
				dwError = GetLastError();
				std::cerr << "Could not open pipe: 5 second wait timed out.";
				__cleanUp(hPipe);
			}
		}



		// 
		// Send a request from client to server
		// 
		std::wstring wsTemp(_requestMessage.begin(), _requestMessage.end());
		const wchar_t* chRequest = wsTemp.c_str();

		int width, height, type;

		//load image with stb
		unsigned char* data = stbi_load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\photo3.bmp", &width, &height, &type, 3);
		int len;
		unsigned char *png = stbi_write_png_to_mem((unsigned char *)data, 0, width, height, type, &len);



		DWORD cbRequest, cbWritten;
		cbRequest = sizeof(chRequest);

		if (!WriteFile(
			hPipe,                      // Handle of the pipe
			png,                  // Message to be written
			len,                  // Number of bytes to write
			&cbWritten,                 // Number of bytes written
			NULL                        // Not overlapped
			))
		{
			dwError = GetLastError();
			wprintf(L"WriteFile to pipe failed w/err 0x%08lx\n", dwError);
			__cleanUp(hPipe);
		}

		wprintf(L"Send %ld bytes to server: \"%s\"\n", cbWritten, chRequest);

		//
		// Receive a response from server.
		// 

		BOOL fFinishRead = FALSE;
		do
		{
			wchar_t chResponse[_bufferSize];
			DWORD cbResponse, cbRead;
			cbResponse = sizeof(chResponse);

			fFinishRead = ReadFile(
				hPipe,                  // Handle of the pipe
				chResponse,             // Buffer to receive the reply
				cbResponse,             // Size of buffer in bytes
				&cbRead,                // Number of bytes read 
				NULL                    // Not overlapped 
				);

			if (!fFinishRead && ERROR_MORE_DATA != GetLastError())
			{
				dwError = GetLastError();
				wprintf(L"ReadFile from pipe failed w/err 0x%08lx\n", dwError);
				__cleanUp(hPipe);
			}

			wprintf(L"Receive %ld bytes from server: \"%s\"\n", cbRead, chResponse);

		} while (!fFinishRead); // Repeat loop if ERROR_MORE_DATA

		__cleanUp(hPipe);

		return dwError;
	}


}