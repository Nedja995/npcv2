// Always include the necessary header files.
// Including SFGUI/Widgets.hpp includes everything
// you can possibly need automatically.
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/processes/IPMatrixApply.h"
#include "npcv/Toolset.h"

//#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/include/thirdparty/stb/stb_image.h"
#include "stdio.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
void reverse(unsigned char* str)
{
	unsigned char* end = str + strlen(reinterpret_cast<char *>(str));
	while (end > str) {
		--end;
		std::swap(*str, *end);
		++str;
	}
}
int main() {
	// Create the main SFML window
	sf::RenderWindow app_window( sf::VideoMode( 800, 600 ), "SFGUI Image Example", sf::Style::Titlebar | sf::Style::Close );

	// We have to do this because we don't use SFML to draw.
	app_window.resetGLStates();

	// Create an SFGUI. This is required before doing anything with SFGUI.
	sfg::SFGUI sfgui;

	// Create our main SFGUI window
	auto window = sfg::Window::Create();
	window->SetTitle( "Title" );

	// Our sf::Image source
	sf::Image sfgui_logo;

	// Our sfg::Image
	auto image = sfg::Image::Create();

	/* npcv */
	npcv::IImageSteam* is = npcv::Toolset::SharedInstance()->imageStream;
	npcv::Image* img = is->Load("D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\input\\pic4.png");



	int width, height, type;
	stbi_set_flip_vertically_on_load(-1);
	//load image with stb
	unsigned char* data = stbi_load("D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\input\\pic4.png", &width, &height, &type, 3 );
	unsigned char *memo = (unsigned char *) malloc(sizeof(unsigned char) * width * height * 3);
	memcpy(memo, data, sizeof(unsigned char) * width * height * 3);
	int ch = 0;

	//FILE* f = fopen(, "rb");

	unsigned char *res_data, *splash_image;
	DWORD res_size;
	int components;
	BITMAPV5HEADER bmh;
	HBITMAP hBitmapRet;
	FILE* f = fopen("D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\input\\pic4.png", "rb");

	if (!f)
		return NULL;

	fseek(f, 0, SEEK_END);
	res_size = ftell(f);
	rewind(f);

	res_data = new unsigned char[res_size];
	fread(res_data, sizeof(unsigned char), res_size, f);
	fclose(f);

	splash_image = stbi_load_from_memory(res_data, res_size, &width, &height, &components, 0);


	/* open file */
	std::fstream fs;
	fs.open("D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\input\\pic4.png", std::ios::in | std::ios::binary | std::ios::ate);
	/* get size */
	size_t size = 0;
	fs.seekg(0, std::ios::end);
	size = fs.tellg();
	fs.seekg(0, std::ios::beg);
	/* copy to buffer */
	char *imgInMemory = new char[size];
	char *header = new char[8];
	fs.read(header, sizeof(char) * 8);
	fs.seekg(0, std::ios::beg);
	fs.read(imgInMemory, size);
	memcpy(header, imgInMemory, sizeof(char) * 8);
	//header[9] = '\n';
	unsigned char* ptr = stbi_load_from_memory(reinterpret_cast<unsigned char*>(imgInMemory), size, &width, &height, &ch, STBI_rgb);

	npcv::Image *imgg = new npcv::Image(ptr, width, height, npcv::PixelType::RGB);


	/*
	* Image apply matrix
	*/
	//make process
	npcv::processing::IPMatrixApply* matrixProc = new npcv::processing::IPMatrixApply();
	//configure process
	matrixProc->setImage(imgg);
	int matrixSize = 3;

	matrixProc->matrixSize = matrixSize;
	float filter[9] =
	{
		1,  1,  1,
		1, -7,  1,
		1,  1,  1
	};
	matrixProc->matrix = &filter[0];
	/*matrixProc->bias = ;
	matrixProc->factor = ;*/

	matrixProc->initialize(); //initialize

	matrixProc->execute();							//execute process

	//free res and delete process
	matrixProc->free();
	delete matrixProc;
	reverse((unsigned char*)img->pixels);
	memcpy(imgInMemory, img->pixels, sizeof(char) * 9);
//	memcpy(imgInMemory, header,  8);
//	memcpy(imgInMemory + 9, img->pixels, img->width * img->height * 3);


	is->Save(imgg, "D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\output\\newImage.png");
	if (data == 0) {
		std::cerr << "cannot load image ";
	}




	// Try to load the image
	if( sfgui_logo.loadFromFile("D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\input\\pic4.png")) {
		//image->SetImage( sfgui_logo );
	}
	if (sfgui_logo.loadFromMemory(imgInMemory, size)) {
		image->SetImage(sfgui_logo);
	}
	// Add the image to the window.
	window->Add( image );

	// Start the game loop
	while ( app_window.isOpen() ) {
		// Process events
		sf::Event event;

		while ( app_window.pollEvent( event ) ) {
			// Handle events
			window->HandleEvent( event );

			// Close window : exit
			if ( event.type == sf::Event::Closed ) {
				app_window.close();
			}
		}

		// Update the GUI, note that you shouldn't normally
		// pass 0 seconds to the update method.
		window->Update( 0.f );

		// Clear screen
		app_window.clear();

		// Draw the GUI
		sfgui.Display( app_window );

		// Update the window
		app_window.display();
	}

	return EXIT_SUCCESS;
}
