#include <iostream>
#include "stdlib.h"
//npcv headers
#include "npcv/Toolset.h"
#include "npcv/geometric/Zoom.h"

using namespace std;
using namespace npcv;

// Tell user what arguents need
static void help() {
	cout << "Need parametars: " << endl;
	cout << "  filepath - image input path" << endl;
	cout << "  filepath - image output path" << endl;
	cout << "  string - \"in\" or \"out\"" << endl;
	cout << "  number - zoom x coeficient" << endl;
	cout << "  number - zoom y coeficient" << endl;
	cout << "Optional:" << endl;
	cout << "  string - zoom type \"replication\" or \"interp\"" << endl;
}

int main(int argc, char* argv[]){
	cout << "NPCV Demo - Zoom Image" << endl;
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
	bool zoomIn = true;
	if (string(argv[3]) == "out") zoomIn = false;
	int coefX = atoi(argv[4]);
	int coefY = atoi(argv[5]);

	// Load image
	Image& img = Toolset::SharedInstance().imageStream.Load(imageInput);
	// Zoom
	img.Zoom(coefX, coefY);
	// Save image
	Toolset::SharedInstance().imageStream.Save(img, imageOutput);

	// Free image and Toolset
	delete &img;
	Toolset::SharedInstance().Free();

	// End
	cout << "NPCV Demo - Zoom Image FINISHED." << endl;
	cout << "Press any key to exit..." << endl;
	char a;
	cin >> a;
	return 0;
}