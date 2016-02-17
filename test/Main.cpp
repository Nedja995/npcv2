
#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/LogListenerDebug.h"
#include "npcv/Toolset.h"
#include "npcv/processes/ProcessGray.h"
#include "npcv/processes/IPMatrixApply.h"
#include "npcv/types/Image.h"
#include "npcv/utils/ImageStreamNP.h"
#include <iostream>

#include <iostream>
#include <chrono>

//#define STB_IMAGE_IMPLEMENTATION
//#include "thirdparty/stb/stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "thirdparty/stb/stb_image_write.h"

using namespace std;
using namespace npcv;
using namespace processing;

void printTime(double miliseconds) {
	if (miliseconds < 1000) {
		cout << "Time: " << miliseconds << " milisec" << endl;
	}
	else {
		cout << "Time: " << miliseconds / 1000 << " sec" << endl;
	}
}

void testImageProcessing();
void testImageStreamNP();

int main(int argc, int *argv[])
{

	testImageStreamNP();

	char in;
	cin >> in;
	return 0;
}

void testImageStreamNP() {
	std::cout << "Test ImageStreamNP" << std::endl;

	npcv::ImageStreamNP* pipeImage = npcv::ImageStreamNP::Create();
	pipeImage->Load(nullptr);


	std::cout << "END Test ImageStreamNP" << std::endl;
}

void testImageProcessing() {
	IImageStream *is = Toolset::SharedInstance()->imageStream;
	//Image * bmi = is->Load("/home/ubuntudev/Desktop/Projects/npcv2/samples/data/input/photo3.bmp");
	//stbi__context* con = new stbi__context();
	//stbi__bmp_load()

	//is->Save(bmi, "D:\\Projects\\NPComputerVision\\npcv2\\samples\\data\\output\\lena.jpg");

	Image * img = Toolset::SharedInstance()->imageStream->Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\photo3.bmp");

	/*
	* graying with divide pixel with 2
	*/
	//make process
	ProcessGray* grayProc = new ProcessGray();
	//configure process
	grayProc->setImage(img);
	grayProc->setIntensity(2);
	grayProc->initialize(); //initialize

	double sum = 0;
	//0
	auto start = std::chrono::steady_clock::now();  //measure start
													//grayProc->execute();							//execute process
	auto end = std::chrono::steady_clock::now();	//measure end
	auto diff = end - start;						//duration
	double milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	sum += milisec;
	cout << "ProcessGray: " << endl;				//function name
	printTime(milisec);
	//////1
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////2
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////3
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////4
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////5
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////6
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////7
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////8
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////9
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);
	////10
	//start = std::chrono::steady_clock::now();  //measure start	
	//grayProc->execute();							//execute process
	//end = std::chrono::steady_clock::now();	//measure end
	//diff = end - start;						//duration
	//milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	//sum += milisec;
	//printTime(milisec);


	//sum /= 11;
	//cout << endl << "Avarage: " << sum << " milis" <<  endl;

	//free res and delete process
	grayProc->free();
	delete grayProc;


	//DebugStream ob;
	// initialize output stream with that output buffer
	//std::ostream out(&ob);

	//ob << "dfdsf";

	//ostream oss();
	//oss << "Fd";

	//DebugStream mc;
	//mc << "fdsfds" << "Fdsfsd";


	/*
	* Image apply matrix
	*/
	//make process
	IPMatrixApply* matrixProc = new IPMatrixApply();
	//configure process
	matrixProc->setImage(img);
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

	start = std::chrono::steady_clock::now();  //measure start
	matrixProc->execute();							//execute process
	end = std::chrono::steady_clock::now();	//measure end
	diff = end - start;						//duration
	milisec = chrono::duration <double, milli>(diff).count(); //miliseconds
	cout << "IPMatrixApply: " << endl;				//function name
	printTime(milisec);
	//free res and delete process
	matrixProc->free();
	delete matrixProc;

	Toolset::SharedInstance()->imageStream->Save(img, "D:\\Projects\\npcv2\\samples\\data\\output\\photo3.bmp");
}