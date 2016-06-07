#include <iostream>
#include "stdlib.h"
//npcv headers
#include "npcv/Toolset.h"
#include "npcv/freatures/EdgeDetectCanny.h"
#include "npcv/segmentation/Treshold.h"

using namespace std;
using namespace npcv;

// Tell user what arguents need
static void help() {
	cout << "Need parametars: " << endl;
	cout << "  filepath - image input path" << endl;
	cout << "  filepath - image output path" << endl;
	cout << "  number - treshold value" << endl;
	cout << "  number - edge detection resolution" << endl;
	cout << "  number - edge detection intensity" << endl;
	cout << "Optional:" << endl;
	cout << "  string - type: canny, itd.." << endl;
	cout << "  number - (canny) 1 for vertical, 0 for horizontal" << endl;
}

int main(int argc, char* argv[]) {
	cout << "NPCV Demo - Edge detection" << endl;
	// Check arhuments
	if (argc < 6) {
		cout << "!Error wrong parametars" << endl;
		help();  
		char a;
		cin >> a;
		return 1;
	}
	// Parse arguments
	string imageInput = argv[1];
	string imageOutput = argv[2];
	int treshold = atoi(argv[3]);
	int edgeResolution = atoi(argv[4]);
	int edgeIntensity = atoi(argv[5]);

	// Load image
	Image& img = Toolset::SharedInstance().imageStream.Load(imageInput);
	/*
	/* EDGE DETECTION 
	*/
	//need grayscaled image
	img.convertToGrayscale();

	Image& edgesVert = freatures::Canny(img, 3, 15, 0, false);
//	Image& edgesHor = freatures::Canny(img, 3, 5, 0, true);
	// Save image
	Toolset::SharedInstance().imageStream.Save(edgesVert, imageOutput);

	// Free image and Toolset
	delete &img;
	Toolset::SharedInstance().Free();

	// End
	cout << "NPCV Demo - Edge detection FINISHED." << endl;
	cout << "Press any key to exit..." << endl;
	char a;
	cin >> a;
	return 0;
}