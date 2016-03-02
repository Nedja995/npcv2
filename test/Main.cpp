#include "npcv/utils/ImageStreamSTB.h"
#include "npcv/LogListenerDebug.h"
#include "npcv/Toolset.h"
#include "npcv/processes/ProcessGray.h"
#include "npcv/processes/IPMatrixApply.h"
#include "npcv/types/Image.h"
#include "npcv/utils/ImageStreamNP.h"
#include "npcv/utils/SamplingImage.h"
#include "npcv/utils/converters/NPipeRequestToImageProcess.h"
#include "npcv/processes/IPBlending.h"
#include "npcv/processes/Erosion.h"

#include <iostream>
#include <chrono>
#include <vector>
//#define STB_IMAGE_IMPLEMENTATION
//#include "thirdparty/stb/stb_image.h"
//#define STB_IMAGE_WRITE_IMPLEMENTATION
//#include "thirdparty/stb/stb_image_write.h"

#define SAMPLE_DATAS std::string("D:\\Projects\\CompVision\\npcv2\\samples\\data\\")

using namespace std;
using namespace npcv;
using namespace processing;

extern Image* npcv::processing::Blend(Image* first, Image* second, float ratio);

void printTime(double miliseconds) {
	if (miliseconds < 1000) {
		cout << "Time: " << miliseconds << " milisec" << endl;
	}
	else {
		cout << "Time: " << miliseconds / 1000 << " sec" << endl;
	}
}

void testImageFilter();
void testImageStreamNP();
void testOCRClassify();
void testBlend();
void testImageArithmetic();
void testImageErosion();

int main(int argc, int *argv[])
{
	//testImageFilter();
	//testImageStreamNP();
	//testOCRClassify();
	//testBlend();
	//testImageArithmetic();
	testImageErosion();

	char in;
	cin >> in;
	return 0;
}

void testImageErosion() {
	IImageStream *is = Toolset::SharedInstance()->imageStream;
	Image * img = is->Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\opencv-logo.png");
	bool cg = img->threshold(200);
	static int i = 0;
	Image * img2 = npcv::processing::Erosion::erosion(img, 1, 0, 8, 
		[](Image* img) {
			img->saveToFile("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\Erosion\\opencv-logo" + std::to_string(i++) + ".bmp");
		});

	cout << "Finish" << endl;
	is->Save(img, "D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\Erosion\\opencv-logo.png");
}

void testImageArithmetic() {
	IImageStream *is = Toolset::SharedInstance()->imageStream;
	Image * img = is->Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\hse1fou1.gif");
	Image * img2 = is->Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\hse1msk3.gif");
	
	Image inp1 = Image(img);
	Image inp2 = Image(img2);
	inp2 += inp1;

	is->Save(&inp2, "D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\tmpl2.png");
}

void testBlend() {
	IImageStream *is = Toolset::SharedInstance()->imageStream;
	Image * img = is->Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\hse1fou1.gif");
	Image * img2 = is->Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\hse1msk3.gif");
	Image inp1 = Image(img);
	Image inp2 = Image(img);

	Image* blended = npcv::processing::Blend(img, img2, 0.5);

	is->Save(blended, "D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\tmpl2.png");
	//npcv::processing::Blend(img, )


}

void testImageStreamNP() {
	std::cout << "Test ImageStreamNP" << std::endl;

	npcv::ImageStreamNP* pipeImage = npcv::ImageStreamNP::Create();
	pipeImage->Load("");


	std::cout << "END Test ImageStreamNP" << std::endl;
}

void testOCRClassify() {
	IImageStream *is = Toolset::SharedInstance()->imageStream;
	Image * img = is->Load(SAMPLE_DATAS + std::string("input\\hwLetters.jpg"));


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
	matrixProc->initialize(); 
	matrixProc->execute();	

	//free
	matrixProc->free();
	delete matrixProc;

	//Image* imageZero = img->getSubImage(20, 20, 20, 20);


	//utils::SamplingImage* samplImage = new utils::SamplingImage(img);
	//std::vector<Image*> digits = samplImage->Subimages(20, 20);

	is->Save(img, SAMPLE_DATAS + std::string("output\\hwLetters.jpg"));

}

void testImageFilter() {
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