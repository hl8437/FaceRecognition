
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

#include "ammem.h"

#pragma comment(lib,"libarcsoft_fsdk_face_detection.lib")
#pragma comment(lib, "libarcsoft_fsdk_face_tracking.lib")
#pragma comment(lib,"libarcsoft_fsdk_age_estimation.lib")
#pragma comment(lib,"libarcsoft_fsdk_face_recognition.lib")
#pragma comment(lib,"libarcsoft_fsdk_gender_estimation.lib")

#define INPUT_IMAGE_PATH "temp.bmp"

using namespace std;
using namespace cv;

bool readBmp(const char* path, uint8_t **imageData, int *pWidth, int *pHeight)
{
	if (path == NULL || imageData == NULL || pWidth == NULL || pHeight == NULL)
	{
		fprintf(stderr, "ReadBmp para error\r\n");
		return false;
	}
	FILE *fp = fopen(path, "rb");
	if (fp == 0)
	{
		fprintf(stderr, "Bmp file open failed\r\n");
		return false;
	}
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);  
	BITMAPINFOHEADER head;
	fread(&head, sizeof(BITMAPINFOHEADER), 1, fp);
	*pWidth = head.biWidth;  	
	*pHeight = head.biHeight;  	
	int biBitCount = head.biBitCount;  	
	int lineByte = ((*pWidth) * biBitCount / 8 + 3) / 4 * 4;  	
	*imageData = (uint8_t *)malloc(lineByte * (*pHeight));  	
	for (int i = 0; i < *pHeight; i++)
	{
		fseek(fp, (*pHeight - 1 - i) * lineByte + 54, SEEK_SET);   	 	
		fread(*imageData + i * (*pWidth) * 3, 1, (*pWidth) * 3, fp);
	}
	fclose(fp);  	
	return true;
} 
int _tmain(int argc, _TCHAR* argv[])
{
	//初始化
	MRESULT nRet = MERR_UNKNOWN;  	
	MHandle hEngine = nullptr;  	
	char APPID[256] = "APPID";  	
	char SDKKey[256] = "SDKKey";  	
	MInt32 nScale = 16;
	MInt32 nMaxFace = 10;
	MByte *pWorkMem = (MByte *)malloc(WORKBUF_SIZE);
	if (pWorkMem == nullptr)
	{
		fprintf(stderr, "fail to malloc workbuf\r\n");
		return -1;
	}
	nRet = AFR_FSDK_InitialEngine(APPID, SDKKey, pWorkMem, WORKBUF_SIZE, &hEngine);
	if (nRet != MOK || hEngine == nullptr)
	{
		fprintf(stderr, "InitialFaceEngine failed , errorcode is %d \r\n", nRet);
		return -1;
	}
	//获取版本信息
	const AFR_FSDK_Version * pVersionInfo = nullptr;  	
	pVersionInfo = AFR_FSDK_GetVersion(hEngine);  	
	fprintf(stdout, "%d %d %d %d %d\r\n", pVersionInfo->lCodebase, pVersionInfo->lMajor, pVersionInfo->lMinor, pVersionInfo->lBuild, pVersionInfo -> lFeatureLevel);  	
	fprintf(stdout, "%s\r\n", pVersionInfo->Version);  	
	fprintf(stdout, "%s\r\n", pVersionInfo->BuildDate);  	
	fprintf(stdout, "%s\r\n", pVersionInfo->CopyRight);
	//读取第一张bmp图片数据
	ASVLOFFSCREEN offInput1 = { 0 };
	offInput1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;  	
	offInput1.ppu8Plane[0] = nullptr;
	readBmp(INPUT_IMAGE1_PATH, (uint8_t**)&offInput1.ppu8Plane[0],&offInput1.i32Width, &offInput1.i32Height);
	if (!offInput1.ppu8Plane[0])
	{
		fprintf(stderr, "fail to ReadBmp(%s)\r\n", INPUT_IMAGE1_PATH);
		AFR_FSDK_UninitialEngine(hEngine);
		free(pWorkMem);  	 	
		return -1;
	}
	offInput1.pi32Pitch[0] = offInput1.i32Width * 3;
	AFR_FSDK_FACEMODEL faceModels1 = { 0 };
	{
		AFR_FSDK_FACEINPUT faceResult;
		//第一张人脸信息通过face detection\face tracking获得  	 	
		faceResult.lOrient = AFR_FSDK_FOC_0;//人脸方向  	 	
		faceResult.rcFace.left = 346;//人脸框位置  	 	
		faceResult.rcFace.top = 58;  	 	
		faceResult.rcFace.right = 440;
		faceResult.rcFace.bottom = 151;
		//提取第一张人脸特征
		AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };
		nRet = AFR_FSDK_ExtractFRFeature(hEngine, &offInput1, &faceResult,&LocalFaceModels);
		if (nRet != MOK)
		{
			fprintf(stderr, "fail to Extract 1st FR Feature, errorcode: %d\r\n", nRet);
		}
		faceModels1.lFeatureSize = LocalFaceModels.lFeatureSize;  	 	
		faceModels1.pbFeature = (MByte*)malloc(faceModels1.lFeatureSize);  	 	
		memcpy(faceModels1.pbFeature, LocalFaceModels.pbFeature, faceModels1.lFeatureSize);
	}

	//读取第二张bmp图片数据
	ASVLOFFSCREEN offInput2 = { 0 };
	offInput2.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;  	
	offInput2.ppu8Plane[0] = nullptr;
	readBmp(INPUT_IMAGE2_PATH, (uint8_t**)&offInput2.ppu8Plane[0],&offInput2.i32Width, &offInput2.i32Height);
	if (!offInput2.ppu8Plane[0])
	{
		fprintf(stderr, "fail to ReadBmp(%s)\r\n", INPUT_IMAGE2_PATH);
		free(offInput1.ppu8Plane[0]);  	 	
		AFR_FSDK_UninitialEngine(hEngine);
		free(pWorkMem);  	 	
		return -1;
	}
	offInput2.pi32Pitch[0] = offInput2.i32Width * 3;
	AFR_FSDK_FACEMODEL faceModels2 = { 0 };
	{
		AFR_FSDK_FACEINPUT faceResult;
		//第二张人脸信息通过face detection\face tracking获得  	 	
		faceResult.lOrient = AFR_FSDK_FOC_0;//人脸方向  	 	
		faceResult.rcFace.left = 122;//人脸框位置  	 	
		faceResult.rcFace.top = 76;  	 	
		faceResult.rcFace.right = 478;
		faceResult.rcFace.bottom = 432;
		//提取第二张人脸特征
		AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };
		nRet = AFR_FSDK_ExtractFRFeature(hEngine, &offInput2, &faceResult,&LocalFaceModels);
		if (nRet != MOK)
		{
			fprintf(stderr, "fail to Extract 2nd FR Feature, error code: %d\r\n", nRet);
		}
		faceModels2.lFeatureSize = LocalFaceModels.lFeatureSize;  	 	
		faceModels2.pbFeature = (MByte*)malloc(faceModels2.lFeatureSize);  	 	
		memcpy(faceModels2.pbFeature, LocalFaceModels.pbFeature, faceModels2.lFeatureSize);
	}
	//对比两张人脸特征，获得比对结果
	MFloat  fSimilScore = 0.0f;  	
	nRet = AFR_FSDK_FacePairMatching(hEngine, &faceModels1, &faceModels2,&fSimilScore);
	if (nRet == MOK)
	{
		fprintf(stdout, "fSimilScore =  %f\r\n", fSimilScore);
	}
	else {
		fprintf(stderr, "FacePairMatching failed , errorcode is %d \r\n", nRet);
	}


	//反初始化
	free(offInput1.ppu8Plane[0]);  	
	free(offInput2.ppu8Plane[0]);  	
	nRet = AFR_FSDK_UninitialEngine(hEngine);
	if (nRet != MOK)
	{
		fprintf(stderr, "UninitialFaceEngine failed , errorcode is %d \r\n", nRet);
	}
	free(pWorkMem);  	
	free(faceModels1.pbFeature);  	
	free(faceModels2.pbFeature);  	
	return 0;

