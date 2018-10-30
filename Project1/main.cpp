#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include "const.h"
#include "FTEngine.h"
#include "AgeEngine.h"
#include "ReadBMP.h"
#include "Engines.h"
#include <stdlib.h>
//#include "SQLEngine.h"
#include "ammem.h"
#include <string>

#pragma comment(lib,"libarcsoft_fsdk_face_detection.lib")
#pragma comment(lib, "libarcsoft_fsdk_face_tracking.lib")
#pragma comment(lib,"libarcsoft_fsdk_age_estimation.lib")
#pragma comment(lib,"libarcsoft_fsdk_face_recognition.lib")
#pragma comment(lib,"libarcsoft_fsdk_gender_estimation.lib")

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
	faceModel1 = engines.getFaceModelFromBMP(path1);
	faceModel2 = engines.getFaceModelFromBMP(path2);
	faceModel3 = engines.getFaceModelFromBMP(path3);
	faceModel4 = engines.getFaceModelFromBMP(path4);
	faceModel5 = engines.getFaceModelFromBMP(path5);
	faceModel6 = engines.getFaceModelFromBMP(path6);
	faceModel7 = engines.getFaceModelFromBMP(path7);
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
	faceModel8 = engines.getFaceModelFromBMP(path8);
	std::cout << "twoManInABmp" <<faceModel8.lFeatureSize << std::endl;
	return 0;

}

int timeAnalyzeOf11Recognition() {
	Engines engines;
	engines.enginesInit();
	const char* path1 = "huanglei.bmp";				// ��С��
	const char* path2 = "huangleiMiddleFace.bmp";	// ����

	AFR_FSDK_FACEMODEL faceModel1 = { 0 };
	AFR_FSDK_FACEMODEL faceModel2 = { 0 };
}

int main() {

	modelSizeAnalyze();
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