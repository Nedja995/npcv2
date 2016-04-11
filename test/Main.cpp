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
#include "npcv/utils/Sampling.h"
#include "npcv/classification/RegionEdge.h"
#include "npcv/freatures/EdgeDetectCanny.h"
#include <iostream>
#include <chrono>
#include <vector>
#include "stdio.h"

//
// SAMPLES DATA PATH STRING
//
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
void testImageZoom();
void testImageSampling();
void testEdgeCanny();
void testImageClassification();

std::vector<int> interpolation(int start, int end, int length) {
	std::vector<int> ret = std::vector<int>();
	int coef = (start > end) ? end : start;
	for (int i = 1; i < length; i++) {
		int val = coef * (((end - start) * i) / length);
		val /= 10;
		ret.push_back(val);
	}
	return ret;
}
void Interpolation() {
	Pixel& A = Pixel::Create(10);
	Pixel& B = Pixel::Create(255);

	int a = A.color(0);
	int b = B.color(0);
	std::vector<int> interps = interpolation(b, a, 10);
	for (int i = 0; i < interps.size(); i++) {
		Image& iter = Image::Create(50, 50, GRAY);
		iter.setColor(interps[i], 0, 0);
		iter.saveToFile(SAMPLE_DATAS + std::string("output\\test\\zoom\\iter" + std::to_string(i) + ".jpg"));
		delete &iter;
	}
//	img.Zoom(6.0f, 6.0f);
//	is.Save(img, SAMPLE_DATAS + std::string("output\\test\\zoom\\5.bmp"));
	//delete &img;
}
Pixel& linearInterpolate(Pixel& A, Pixel& B, int l, int L) {
	// extract r, g, b information
	// A and B is a ARGB-packed int so we use bit operation to extract
	int Ar = A.color(0);
	int Ag = A.color(1);
	int Ab = A.color(2);
	int Br = B.color(0);
	int Bg = B.color(1);
	int Bb = B.color(2);
	// now calculate Y. convert float to avoid early rounding
	// There are better ways but this is for clarity's sake
	int Yr = (int)(Ar + l*(Br - Ar) / (float)L);
	int Yg = (int)(Ag + l*(Bg - Ag) / (float)L);
	int Yb = (int)(Ab + l*(Bb - Ab) / (float)L);

	return Pixel::Create(Yr, Yg, Yb);
}
void zoomInterp() {
	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\0.jpg"));
	img.convertToGrayscale();

	int xs = 6.0f;
	int ys = 6.0f;
	int sw = xs * img.width;
	int sh = ys * img.height;

	Pixel& red = Pixel::Create(255, 0, 0);
	Pixel& green = Pixel::Create(0, 255, 0);
	Pixel& px = linearInterpolate(red, green, 5, 7);
	int r = px.color(0);
	int g = px.color(1);
	int b = px.color(2);
	Image& simg = Image::Create(sw, sh, GRAY);

	for (int x = 0; x < img.width - 1; x++) {
		for (int y = 0; y < img.height - 1; y++) {
			int x1Start = *img.pixelPtr(x, y);
			int x1End = *img.pixelPtr(x + 1, y);
			int y1Start = *img.pixelPtr(x, y);
			int y1End = *img.pixelPtr(x, y + 1);
			std::vector<int> xInters = interpolation(x1Start, x1End, xs);
			std::vector<int> yInters = interpolation(y1Start, y1End, ys);
			for (int i = 0; i < yInters.size(); i++) {
				std::vector<int> xyInters = interpolation(yInters[i], y1End, xs);
			}
			for (int i = 0; i < xInters.size(); i++) {
				simg.setPixel(x * xs + i, y * ys , xInters[i]);
				/*for (int j = 0; j < xInters.size(); j++) {
					simg.setPixel(x * 0e + i, y * ys + j, xInters[i]);
				}*/
			}
		}
	}

	simg.saveToFile(SAMPLE_DATAS + std::string("output\\test\\zoom\\interp.jpg"));
}

int main(int argc, int *argv[])
{
//	testImage();
//	testImageConvolutionMatrix();
//	testImageArithmetic();
//	testImageSegmentation();
//	testImageErosion();
//	testImageZoom();
//	testImageSampling();
//	testImageClassification();
	testEdgeCanny();
//	Interpolation();
//	zoomInterp();
	//testImageStreamNP();
	//testOCRClassify();
	//testBlend();

//	testImageFilter();


	Toolset::Free();

	char in;
	//cin >> in;
	return 0;
}
void testEdgeCanny() {
	cout << "Start image edge tection - Canny" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\digitsSmall.jpg"));
	
	img.convertToGrayscale();
	
	bool cg = segmentation::Treshold::global(img, 250);
//	img.Zoom(3.0f, 3.0f);
	Image& edgesVert = freatures::Canny(img, 1, 100, 0, true);
	Image& edgesHoriz = freatures::Canny(img, 1, 100, 0, false);
//	Image& add = edgesVert + edgesHoriz;

	is.Save(edgesVert, SAMPLE_DATAS + std::string("output\\test\\freatures\\cannyVerDigitsSmall.jpg"));
	is.Save(edgesHoriz, SAMPLE_DATAS + std::string("output\\test\\freatures\\cannyHorDigitsSmall.jpg"));
//
	delete &img;

	cout << "End image edge tection - Canny" << endl;
}
void testImageClassification()
{
	cout << "Start image classification test - region edge based" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\digitsSmall.jpg"));
	//img.Zoom(10.0f, 10.0f);
	vector<Image*> zeros = sampling::Subimages(img, 20, 20);// 97, 97);
	static int i = 0;
	for each (Image* chSample in zeros)
	{
		chSample->Zoom(6.0f, 6.0f);
		Pixel& foreground = Pixel::Create(255);

		static int erCount = 0;
		erCount = 0;
		bool cg = segmentation::Treshold::global(*chSample, 100);
		//is.Save(*chSample, SAMPLE_DATAS + std::string("output\\test\\sampling\\digitsSmall\\"+ std::to_string(i) +"digitsSmall.jpg"));
		npcv::processing::Erosion::erosion(*chSample, 1, foreground,
			[](Image& imga) {
			if (erCount++ == 4) {
				auto edges = freatures::Canny(imga, 5, 100, 0, true);
				auto reg = classify::GetRegions(imga, imga.width / 5, imga.height / 5, 0);
			}
		});
		i++;

		delete chSample;
	}
	//is.Save(img, SAMPLE_DATAS + std::string("output\\test\\sampling\\digitsSmall\\digitsSmall.jpg"));

	delete &img;

	cout << "End image test - ZOOM" << endl;
}

void testImageSampling()
{
	cout << "Start image sampling test - subimages" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\digitsSmall.jpg"));
	//img.Zoom(10.0f, 10.0f);
	vector<Image*> zeros = sampling::Subimages(img, 20, 20);// 97, 97);
	static int i = 0;
	for each (Image* chSample in zeros)
	{
		chSample->Zoom(6.0f, 6.0f);
		Pixel& foreground = Pixel::Create(255);
		
		static int erCount = 0;
		erCount = 0;
		bool cg = segmentation::Treshold::global(*chSample, 100);
		//is.Save(*chSample, SAMPLE_DATAS + std::string("output\\test\\sampling\\digitsSmall\\"+ std::to_string(i) +"digitsSmall.jpg"));
		npcv::processing::Erosion::erosion(*chSample, 1, foreground,
			[](Image& imga) {
			if (erCount++ == 4) {
				Toolset::SharedInstance().imageStream.Save(imga, SAMPLE_DATAS + std::string("output\\test\\sampling\\digitsSmall\\" + std::to_string(i) + "-" + std::to_string(erCount) + ".jpg"));
			}	
		});
		i++;
		
		delete chSample;
	}
	//is.Save(img, SAMPLE_DATAS + std::string("output\\test\\sampling\\digitsSmall\\digitsSmall.jpg"));

	delete &img;

	cout << "End image test - ZOOM" << endl;
}

void testImageZoom() {
	cout << "Start image test - ZOOM" << endl;

	IImageStream& is = Toolset::SharedInstance().imageStream;
	Image& img = is.Load(SAMPLE_DATAS + std::string("input\\5.bmp"));

	img.Zoom(6.0f, 6.0f);

	is.Save(img, SAMPLE_DATAS + std::string("output\\test\\zoom\\5.bmp"));

	delete &img;

	cout << "End image test - ZOOM" << endl;
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
	Image& img = is.Load("D:\\Projects\\CompVision\\npcv2\\samples\\data\\input\\3.jpg");

	bool cg = segmentation::Treshold::global(img, 100);
	static int i = 0;
//	img.saveToFile("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\test\\morphology\\erosion\\7" + std::to_string(i++) + ".bmp");
/*	Image& img2 = npcv::processing::Erosion::erosion(img, 1, 0, 5, 
		[](Image& img) {
			img.saveToFile("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\test\\morphology\\erosion\\opencv-logo" + std::to_string(i++) + ".bmp");
		});
*/

	Pixel& foreground = Pixel::Create(0);
	npcv::processing::Erosion::erosion(img, 1, foreground, 
		[](Image& img) {
		if (i++ == 24) {

		img.saveToFile("D:\\Projects\\CompVision\\npcv2\\samples\\data\\output\\test\\morphology\\erosion\\3" + std::to_string(i++) + ".jpg");
		}
	});
	delete &img;
	delete &foreground;
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
	
	_testImageAdd();
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