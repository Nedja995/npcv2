#include <iostream>
#include "stdlib.h"
//npcv headers
#include "npcv/Toolset.h"
#include "npcv/filters/IPMatrixApply.h"

using namespace std;
using namespace npcv;

// Tell user what arguents need
static void help() {
	cout << "Need parametars: " << endl;
	cout << "  filepath - image input path" << endl;
	cout << "  filepath - image output path" << endl;
	cout << "  number - rows" << endl;
	cout << "  number - columns" << endl;
	cout << "  number array - matrix members" << endl;
}

int main(int argc, char* argv[]) {
	cout << "NPCV Demo - Convolution Matrix" << endl;
	// Check arhuments
	if (argc < 6) {
		cout << "!Error wrong parametars" << endl;
		help();
		char a;
		cin >> a;
		return 1;
	}
	for (int i = 0; i < argc; i++) {
		char* s = argv[i];
		int a = 2;
	}
	// Parse arguments
	// //paths
	string imageInput = argv[1];
	string imageOutput = argv[2];
	int rows = atoi(argv[3]);
	int cols = atoi(argv[4]);
	if (rows * cols + 5 != argc) {
		cout << "!Error wrong parametars" << endl;
		help();
		char a;
		cin >> a;
		return 1;
	}
	// fill matrix arguments
	int size = rows * cols;
	float* matrix = new float[size];
	for (int i = 0; i < size; i++){
		float arg = atof(argv[5 + i]);
		matrix[i] = arg;
	}

	// Load image
	Image& img = Toolset::SharedInstance().imageStream.Load(imageInput);

	/*
	* Image apply matrix
	*/
	//make process
	processing::IPMatrixApply* matrixProc = new processing::IPMatrixApply();
	//configure process
	matrixProc->setImage(&img);
	int matrixSize = 3;

	matrixProc->matrixSize = matrixSize;

	matrixProc->matrix = &matrix[0];
	/*matrixProc->bias = ;
	matrixProc->factor = ;*/

	matrixProc->initialize(); //initialize

	matrixProc->execute();//execute process

	////free res and delete process
	//matrixProc->free();
	delete matrixProc;

	// Save image
	Toolset::SharedInstance().imageStream.Save(img, imageOutput);

	// Free image and Toolset
	delete &img;
	Toolset::SharedInstance().Free();

	// End
	cout << "NPCV Demo - Convolution Matrix FINISHED." << endl;
	cout << "Press any key to exit..." << endl;
	char a;
	cin >> a;
	return 0;
}