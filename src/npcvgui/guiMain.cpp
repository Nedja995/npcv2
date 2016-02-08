// Always include the necessary header files.
// Including SFGUI/Widgets.hpp includes everything
// you can possibly need automatically.
#include <SFGUI/SFGUI.hpp>
#include <SFGUI/Widgets.hpp>

#include <SFML/Graphics.hpp>

#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/processes/IPMatrixApply.h"
#include "npcv/Toolset.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#define STB_IMAGE_IMPLEMENTATION
#include "../thirdparty/include/thirdparty/stb/stb_image.h"
#include "../thirdparty/include/thirdparty/stb/stb_image_write.h"

#include "stdio.h"
#include <Windows.h>
#include <iostream>
#include <fstream>

npcv::Image* img;
npcv::processing::IPMatrixApply* matrixProc;
int matrixSize = 3;
float filter[9] =
{
	1,  1,  1,
	1, -7,  1,
	1,  1,  1
};

// Our sf::Image source
sf::Image sfgui_logo;
// Our sfg::Image
std::shared_ptr<sfg::Image> image;

extern unsigned char *stbi_write_png_to_mem(unsigned char *pixels, int stride_bytes, int x, int y, int n, int *out_len);
// Create our adjustment smart pointer.
sfg::Adjustment::Ptr m_adjustment;
void AdjustmentChange() {
	std::stringstream sstr;
	sstr << m_adjustment->GetValue();
//	matrixProc->bias = m_adjustment->GetValue() / 5;
	matrixProc->execute();
	int len;
	unsigned char *imgFile = stbi_write_png_to_mem((unsigned char *)img->pixels, 0, img->width, img->height, img->type, &len);

	/* Show image */

	if (sfgui_logo.loadFromMemory(imgFile, len)) {
		image->SetImage(sfgui_logo);
	}
}


int main2() {
	// Create the main SFML window
	sf::RenderWindow app_window( sf::VideoMode( 800, 600 ), "SFGUI Image Example", sf::Style::Titlebar | sf::Style::Close );

	// We have to do this because we don't use SFML to draw.
	app_window.resetGLStates();

	// Create an SFGUI. This is required before doing anything with SFGUI.
	sfg::SFGUI sfgui;

	// Create our main SFGUI window
	auto window = sfg::Window::Create();
	window->SetTitle( "Title" );

	/*
	* SCROLLBAR
	*/
	// Create our box.
	auto box = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL);

	// Create the scrollbar.
	// We want a vertical scrollbar.
	auto scrollbar = sfg::Scrollbar::Create(sfg::Scrollbar::Orientation::VERTICAL);

	m_adjustment = scrollbar->GetAdjustment();

	// Tune the adjustment parameters.
	m_adjustment->SetLower(20.f);
	m_adjustment->SetUpper(100.f);

	// How much it should change when clicked on the stepper.
	m_adjustment->SetMinorStep(3.f);

	// How much it should change when clicked on the trough.
	m_adjustment->SetMajorStep(12.f);
	// Additionally you can connect to the OnChange signal of an adjustment
	// to get notified when any of it's parameters are changed.
	m_adjustment->GetSignal(sfg::Adjustment::OnChange).Connect(AdjustmentChange);

	// Just as with the entry widget we set custom requisitions for our
	// range widgets to make sure they don't look strange.

	scrollbar->SetRequisition(sf::Vector2f(0.f, 80.f));

	// To keep our scale's slider from expanding too much we use another box
	// set to verticle orientation.
	auto scalebox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL);


	// Pack into box
	box->Pack(scalebox);
	box->Pack(scrollbar);

	// Set box spacing
	box->SetSpacing(5.f);
	// CAUTION:
	// Normally you would only set the page size for scrollbar adjustments.
	// For demonstration purposes we do this for our scale widget too.
	// If page size isn't 0 a scale widget won't be able to be set to it's
	// maximum value. This is in fact also true for scrollbars, however
	// because they are used to scroll the page size must be subtracted from
	// the maximum.
	m_adjustment->SetPageSize(20.f);


	// Additionally you can connect to the OnChange signal of an adjustment
	// to get notified when any of it's parameters are changed.
	m_adjustment->GetSignal(sfg::Adjustment::OnChange).Connect(AdjustmentChange);

	// Just as with the entry widget we set custom requisitions for our
	// range widgets to make sure they don't look strange.
	scrollbar->SetRequisition(sf::Vector2f(0.f, 80.f));


	// Pack into box
	box->Pack(scalebox);
	box->Pack(scrollbar);

	// Set box spacing
	box->SetSpacing(5.f);



	sf::Clock clock;


	image = sfg::Image::Create();




	/* npcv */
	npcv::IImageSteam* is = npcv::Toolset::SharedInstance()->imageStream;
	img = is->Load("D:\\Projects\\npcv2\\samples\\data\\input\\lena.jpg");

	/*
	* Image apply matrix
	*/
	//make process
	matrixProc = new npcv::processing::IPMatrixApply();
	
	//configure process
	matrixProc->setImage(img);
	matrixProc->matrixSize = matrixSize;

	matrixProc->matrix = &filter[0];
	/*matrixProc->bias = ;
	matrixProc->factor = ;*/

	//initialize process
	matrixProc->initialize(); 
	//execute process
	//matrixProc->execute();
	//free res and delete process
	//matrixProc->free();
	//delete matrixProc;

	/* Load processed image to memory */
	int len;
	unsigned char *imgFile = stbi_write_png_to_mem((unsigned char *)img->pixels, 0, img->width, img->height, img->type, &len);
	
	/* Show image */

	if (sfgui_logo.loadFromMemory(imgFile, len)) {
		image->SetImage(sfgui_logo);
	}
	box->Pack(image);
	// Add our box to the window
	window->Add(box);
	// Add the image to the window.
	//window->Add( image );

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
