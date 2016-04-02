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
#include "npcv/processes/Treshold.h"

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

void testImage();
void testImageConvolutionMatrix();
void testImageFilter();
void testImageStreamNP();
void testOCRClassify();
void testBlend();
void testImageArithmetic();
void testImageErosion();
void testImageSegmentation();


int main(int argc, int *argv[])
{

//	testImage();
//	testImageConvolutionMatrix();
//	testImageArithmetic();
//	testImageSegmentation();
	testImageErosion();

	 
	//testImageStreamNP();
	//testOCRClassify();
	//testBlend();

//	testImageFilter();


	Toolset::Free();

	char in;
	//cin >> in;
	return 0;
}

void testImageConvolutionMatrix() {
	cout << "Start processing test - CONVOLUTION MATRIX" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\photo3.bmp"));

	/*
	* Image apply matrix
	*/
	//make process
	IPMatrixApply* matrixProc = new IPMatrixApply();
	//configure process
	matrixProc->setImage(&img);
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

	////free res and delete process
	//matrixProc->free();
	delete matrixProc;



	is.Save(img, SAMPLE_DATAS + std::string("output\\test\\matrixphoto3.bmp"));

	delete &img;

	cout << "End processing test - CONVOLUTION MATRIX" << endl;
}

void testImageErosion() {
	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\opencv-logo.png");
	bool cg = segmentation::Treshold::global(img, 100);
	static int i = 0;

/*	Image& img2 = npcv::processing::Erosion::erosion(img, 1, 0, 5, 
		[](Image& img) {
			img.saveToFile("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\test\\morphology\\erosion\\opencv-logo" + std::to_string(i++) + ".bmp");
		});
*/

	Pixel& foreground = Pixel::Create(0);
	npcv::processing::Erosion::erosion(img, 3, foreground, 
		[](Image& img) {
		img.saveToFile("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\test\\morphology\\erosion\\opencv-logo" + std::to_string(i++) + ".bmp");
	});

	//cout << "Finish" << endl;
	//is.Save(img, "D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\Erosion\\opencv-logo.png");
}

void _testImageAdd();
void _testImageSubstract();

void testImageSegmentation() {
	cout << "Start segmentation test - TRESHOLD" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\lena.jpg"));

	segmentation::Treshold::global(img, 100);

	is.Save(img, SAMPLE_DATAS + std::string("output\\test\\segmentation\\globalTresholdLena.jpg"));

	delete &img;

	cout << "End segmentation test - TRESHOLD" << endl;
}

void testImageArithmetic() {
	
//	_testImageAdd();
	_testImageSubstract();
}

void testImage() {
	cout << "Start image test - GRAYSCALE" << endl;

	Toolset ts = Toolset::SharedInstance();
	IImageStream& is = ts.imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\lena.jpg"));

	bool c = img.convertToGrayscale();

	is.Save(img, SAMPLE_DATAS + std::string("output\\test\\grayLena.jpg"));

	delete &img;
//	delete &ts;
	//Toolset::Free();
	cout << "End image test - GRAYSCALE" << endl;
}

void _testImageAdd() {
	cout << "Start image artihmetic - ADD" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\test\\flower.jpg"));
	Image& img2 = is.Load(SAMPLE_DATAS + std::string("input\\test\\cows.jpg"));

	Image& add =  img + img2;
	Image& add2 = img + img2;
	img2 += img;

	is.Save(add, SAMPLE_DATAS + std::string("output\\test\\arithmetic\\AddflowerCows.jpg"));
	is.Save(add2, SAMPLE_DATAS + std::string("output\\test\\arithmetic\\AddflowerCows2.jpg"));
	is.Save(img2, SAMPLE_DATAS + std::string("output\\test\\arithmetic\\AddAssignflowerCows.jpg"));
	
	delete &add;
	delete &add2;
	delete &img;
	delete &img2;
	
	cout << "End image artihmetic - ADD" << endl;
}

void _testImageSubstract() {
	cout << "Start image artihmetic - SUBSTRACTION" << endl;
	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\test\\cows.jpg"));
	Image& img2 = is.Load(SAMPLE_DATAS + std::string("input\\test\\horses.jpg"));

	Image& sub = img - img2;
	Image& sub2 = img - img2;
	img2 -= img;

	is.Save(sub, SAMPLE_DATAS + std::string("output\\test\\arithmetic\\SubstractionHorserCows.jpg"));
	is.Save(sub2, SAMPLE_DATAS + std::string("output\\test\\arithmetic\\SubstractionHorserCows2.jpg"));
	is.Save(img2, SAMPLE_DATAS + std::string("output\\test\\arithmetic\\SubstractionAssignHorserCows.jpg"));

	delete &sub;
	delete &sub2;
	delete &img;
	delete &img2;

	cout << "End image artihmetic - SUBSTRACTION" << endl;
}

void testBlend() {
	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\hse1fou1.gif");
	Image& img2 = is.Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\hse1msk3.gif");
	Image inp1 = Image(img);
	Image inp2 = Image(img);

	Image* blended = npcv::processing::Blend(&img, &img2, 0.5);

	is.Save(*blended, "D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\tmpl2.png");
	//npcv::processing::Blend(img, )


}

void testImageStreamNP() {
	std::cout << "Test ImageStreamNP" << std::endl;

	npcv::ImageStreamNP* pipeImage = npcv::ImageStreamNP::Create();
	pipeImage->Load("");


	std::cout << "END Test ImageStreamNP" << std::endl;
}

void testOCRClassify() {
	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\lena.jpg"));


	/*
	* Image apply matrix
	*/
	//make process
	IPMatrixApply* matrixProc = new IPMatrixApply();
	//configure process
	matrixProc->setImage(&img);
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

	is.Save(img, SAMPLE_DATAS + std::string("output\\lena.jpg"));

}

void testImageFilter() {
	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\photo3.bmp");

	/*
	* graying with divide pixel with 2
	*/
	//make process
	ProcessGray* grayProc = new ProcessGray();
	//configure process
	grayProc->setImage(&img);
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

	Toolset::SharedInstance().imageStream.Save(img, SAMPLE_DATAS + std::string("output\\photo3.bmp"));
}