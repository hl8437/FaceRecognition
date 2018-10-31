#include "Engines.h"
#include <iostream>
#include <windows.h>

#include <opencv.hpp>


#define INPUT_IMAGE_PATH "temp.bmp"


int modelSizeAnalyze() {
	/*
	���ۣ�
	1. ������С��Ӱ��
	2. bmpͼ���ܹ���
	3. bmpͼ����һ����С�ڲ�Ӱ��faceModel��С

	4.˫��ͼ��Ӱ����

	����22020 byte -> 22K����
	*/

	Engines engines;
	engines.enginesInit();
	/* 900KͼƬ������С��ͬ */
	const char* path1 = "huanglei.bmp";				// ��С��
	const char* path2 = "huangleiMiddleFace.bmp";	// ����
	const char* path3 = "huangleiBigFace.bmp";		// ����
	/* 500KͼƬ */
	const char* path4 = "netPhoto1.bmp";
	/* 3M ͼ��*/
	const char* path5 = "xiaoyang.bmp";
	/*1.5M*/
	const char* path6 = "xiaoyang720.bmp";
	/*22M*/
	const char* path7 = "huanglei22M.bmp";

	AFR_FSDK_FACEMODEL faceModel1 = { 0 };
	AFR_FSDK_FACEMODEL faceModel2 = { 0 };
	AFR_FSDK_FACEMODEL faceModel3 = { 0 };
	AFR_FSDK_FACEMODEL faceModel4 = { 0 };
	AFR_FSDK_FACEMODEL faceModel5 = { 0 };
	AFR_FSDK_FACEMODEL faceModel6 = { 0 };
	AFR_FSDK_FACEMODEL faceModel7 = { 0 };

	ASVLOFFSCREEN offInput1 = { 0 };
	faceModel1 = engines.getFaceModelFromBMP(path1, &offInput1);
	faceModel2 = engines.getFaceModelFromBMP(path2, &offInput1);
	faceModel3 = engines.getFaceModelFromBMP(path3, &offInput1);
	faceModel4 = engines.getFaceModelFromBMP(path4, &offInput1);
	faceModel5 = engines.getFaceModelFromBMP(path5, &offInput1);
	faceModel6 = engines.getFaceModelFromBMP(path6, &offInput1);
	faceModel7 = engines.getFaceModelFromBMP(path7, &offInput1);
	std::cout << faceModel1.lFeatureSize << std::endl;
	std::cout << faceModel2.lFeatureSize << std::endl;
	std::cout << faceModel3.lFeatureSize << std::endl;
	std::cout << faceModel4.lFeatureSize << std::endl;
	std::cout << faceModel5.lFeatureSize << std::endl;
	std::cout << faceModel6.lFeatureSize << std::endl;
	std::cout << faceModel7.lFeatureSize << std::endl;
	std::cout << "sizeof(int):" << sizeof(int) << std::endl;
	std::cout << "sizeof(MByte):" << sizeof(MByte) << std::endl;
	std::cout << "sizeof(MInt)" << sizeof(MInt32) << std::endl;

	const char* path8 = "netPhoto3.bmp";
	AFR_FSDK_FACEMODEL faceModel8 = { 0 };
	faceModel8 = engines.getFaceModelFromBMP(path8, &offInput1);
	std::cout << "twoManInABmp" <<faceModel8.lFeatureSize << std::endl;
	return 0;

}

int timeAnalyzeOf11Recognition() {
	//1:1ʱ�����	
	//ʮ���			ms
	// ͬ��ͬ��			10906
	// ͬ�˲�ͬ��		10859
	// ��ͬ��			10860
	Engines engines;
	engines.enginesInit();
	const char* path1 = "huanglei.bmp";				
	const char* path2 = "netPhoto1.bmp";	

	AFR_FSDK_FACEMODEL faceModel1 = { 0 };
	AFR_FSDK_FACEMODEL faceModel2 = { 0 };

	ASVLOFFSCREEN offInput;
	offInput = { 0 };
	
	faceModel1 = engines.getFaceModelFromBMP(path1, &offInput);
	
	faceModel2 = engines.getFaceModelFromBMP(path2, &offInput);

	MFloat fimiliarScore;
	std::cout << "click to start" << std::endl;
	getchar();
	std::cout << "��ʼ" << std::endl;
	double start = GetTickCount();
	for (int i = 0; i < 10000; i++)
	{
		engines.faceRecognition(&faceModel1, &faceModel2, &fimiliarScore);
	}
	double end = GetTickCount();
	std::cout << "over" << std::endl;
	std::cout << "Time consume of 11 recognition is	" << end - start << "ms?" << std::endl;
	return 0;
	
}

int timeAnalyzeOfExtractModelFromOffInput() {

	// ǧ���֮һ�뼶��

	Engines engines;
	engines.enginesInit();
	/* 900KͼƬ������С��ͬ */
	const char* path1 = "huanglei.bmp";				// ��С��
	const char* path2 = "huangleiMiddleFace.bmp";	// ����
	const char* path3 = "huangleiBigFace.bmp";		// ����
	/* 500KͼƬ */
	const char* path4 = "netPhoto1.bmp";
	/* 3M ͼ��*/
	const char* path5 = "xiaoyang.bmp";
	/*1.5M*/
	const char* path6 = "xiaoyang720.bmp";
	/*22M*/
	const char* path7 = "huanglei22M.bmp";

	ASVLOFFSCREEN offInput1 = { 0 };
	AFR_FSDK_FACEMODEL faceModel1 = { 0 };
	offInput1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	offInput1.ppu8Plane[0] = nullptr;
	readBMP(path2, &offInput1.ppu8Plane[0], &offInput1.i32Width, &offInput1.i32Height);

	LPAFT_FSDK_FACERES faceRes;
	engines.faceTracking(&offInput1, &faceRes);
	AFR_FSDK_FACEINPUT frinput = { 0 };
	engines.getFRFaceInput(faceRes, &frinput);

	double start = GetTickCount();
	for (double i = 0; i < 1000; i++)
	{
		engines.extractFRFeature(&offInput1, &frinput, &faceModel1);
	}
		
	double end = GetTickCount();
	std::cout << end - start << std::endl;
	
	return 0;

}

int timeAnalyzeOfCaptureToOffInput() {

	// ���� capture>>frame 10�� 328ms  100��3296
	// ����capture֡�� 30
	// engines.cameraToOffInput(&capture, &frame, &offInput); 100�� 4781ms

	// ��offinput-��faceRes ���֮һ�뼶��


	cv::VideoCapture capture;
	cv::Mat frame;
	Engines engines;
	engines.enginesInit();
	ASVLOFFSCREEN offInput;
	LPAFT_FSDK_FACERES pFaceRes;

	capture.open(0);
	if (!capture.isOpened())
	{
		std::cout << "����ͷδ��" << std::endl;
		return -1;
	}
	double fps = capture.get(CV_CAP_PROP_FPS);
	std::cout << fps << std::endl;
	
	engines.cameraToOffInput(&capture, &frame, &offInput);
	
	std::cout << offInput.i32Height << std::endl;
	std::cout << offInput.i32Width << std::endl;

	double start = GetTickCount();
	std::cout << "kaishi" << std::endl;
	for (int i = 0; i < 1000000; i++)
	{	
		pFaceRes = new AFT_FSDK_FACERES;
		engines.faceTracking(&offInput, &pFaceRes);
		free(pFaceRes);
	}
	double end = GetTickCount();
	std::cout << end - start << std::endl;
	return 0;

}

int main() {
	
	timeAnalyzeOfCaptureToOffInput();
	getchar();
	return 0;
}


//int test() {
//	/* ����engine */
//	MRESULT nRet = MERR_UNKNOWN;
//	Engines engines;
//
//	/* engines ��ʼ�� */
//	nRet = engines.enginesInit();
//	if (!nRet == MOK)
//	{
//		std::cout << "��ʼ������ʧ��" << std::endl;
//		return nRet;
//	}
//
//	/* engines ������Դ������ʼ�� */
//	engines.initFaceVariables();
//
//	/* ����ͷ */
//	engines.initCamera();
//
//	engines.getFaceModelFromBMP();
//	std::cout << "����������" << std::endl;
//	cv::waitKey(1000);
//	/* ������ʵ�� */
//	while (true)
//	{
//		engines.cameraToOffInput();
//		engines.faceTracking();
//
//		engines.getVideoFaceModel();
//		engines.faceRecognitionOneToOne();
//
//		std::cout << engines.tempFimiliar << std::endl;
//		engines.showVideo();
//
//		if (cv::waitKey(30) >= 0)
//		{
//			break;
//		}
//
//		///* Very important */
//		//free(offInput.ppu8Plane[0]);
//	}
//
//	engines.releaseCamera();
//	return 0;
//}