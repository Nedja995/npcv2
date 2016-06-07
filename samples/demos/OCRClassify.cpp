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
	cout << "  filepath - image input path. Characters in grid layout like digits.jpg" << endl;
	cout << "  filepath - output csv." << endl;
	cout << "  number - sample size." << endl;
}

int main(int argc, char* argv[]){
	cout << "NPCV Demo - OCR Classify" << endl;
	// Check arhuments
	if (argc < 4) {
		cout << "!Error wrong parametars" << endl;
		help();
		char a;
		cin >> a;
		return 1;
	}
	// Parse arguments
	string imageInput = argv[1];
	string csvOutput = argv[2];
	int sampleSize = atoi(argv[3]);

	// Load image
	Image& img = Toolset::SharedInstance().imageStream.Load(imageInput);

	// Classify here

	// Save csv

	// Free image and Toolset
	delete &img;
	Toolset::SharedInstance().Free();

	// End
	cout << "NPCV Demo - OCR Classify FINISHED." << endl;
	cout << "Press any key to exit..." << endl;
	char a;
	cin >> a;
	return 0;
}