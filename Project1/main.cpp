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



int main() {

	/* 声明engine */
	MRESULT nRet = MERR_UNKNOWN;
	Engines engines;
	
	/* engines 初始化 */
	nRet = engines.enginesInit();
	if (!nRet == MOK)
	{
		std::cout << "初始化引擎失败" << std::endl;
		return nRet;
	}

	/* engines 人脸资源变量初始化 */
	engines.initFaceVariables();

	/* 摄像头 */
	engines.initCamera();

	engines.getFaceModelFromBMP();
	std::cout << "进入主功能" << std::endl;
	cv::waitKey(1000);
	/* 主功能实现 */
	while (true)
	{
		
		engines.cameraToOffInput();
		engines.faceTracking();
		
		engines.getVideoFaceModel();
		engines.faceRecognitionOneToOne();
		
		std::cout << engines.tempFimiliar << std::endl;
		engines.showVideo();

		if (cv::waitKey(30) >= 0)
		{
			break;
		}

		///* Very important */
		//free(offInput.ppu8Plane[0]);
	}
	
	/*capture.release();*/
	return 0;
}


///* 获得性别评估输入 FaceRes */
////genderFaceInput 与 FaceResult 类型可转换
//genderFaceInput.lFaceNumber = FaceRes->nFace;
//genderFaceInput.pFaceRectArray = FaceRes->rcFace;
//genderFaceInput.pFaceOrientArray = &(FaceRes->lfaceOrient);

///* 获得年龄评估输入 */

//
///* 获得对比输入 */
//tempFaceResult.lOrient = FaceRes->lfaceOrient;
//tempFaceResult.rcFace = *(FaceRes->rcFace);

////获得genderResult
//genderEngine.GenderEstimationPreview(&offInput, &genderFaceInput, &genderResult);
//ageEngine.AgeEstimationPreview(&offInput, &ageFaceInput, &ageResult);
//
//AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };
//nRet = frEngine.ExtractFRFeature(&offInput, &tempFaceResult, &LocalFaceModels);
//if (nRet != MOK)
//{
//	//fprintf(stderr, "fail to Extract 2nd FR Feature, error code: %d\r\n", nRet);
//}
//tempFaceModels.lFeatureSize = LocalFaceModels.lFeatureSize;
//tempFaceModels.pbFeature = (MByte*)malloc(tempFaceModels.lFeatureSize);
//memcpy(tempFaceModels.pbFeature, LocalFaceModels.pbFeature, tempFaceModels.lFeatureSize);

//nRet = frEngine.FacePairMatching(&localFaceModels1, &tempFaceModels, &fSimilScore);
//if (nRet == MOK)
//{
//	//fprintf(stdout, "fSimilScore =  %f\r\n", fSimilScore);
//}
//else {
//	//fprintf(stderr, "FacePairMatching failed , errorcode is %d \r\n", nRet);
//}


//if (nRet == MOK)
//{
//	//fprintf(stdout, "The number of face: %d\r\n", FaceRes->nFace);
//	for (int i = 0; i < FaceRes->nFace; ++i)
//	{
//		//在视频上画出矩形
//		cv::rectangle(frame, CvPoint(FaceRes->rcFace[i].left, FaceRes->rcFace[i].top), CvPoint(FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom), CvScalar(255, 0, 0), 2);
//		
//		//在矩形底部打印信息
//		sprintf(age, "%d", ageResult.pAgeResultArray[i]);
//		info = "name:" + name + "sex" + sex[genderResult.pGenderResultArray[i] + 1] + "age" + age;
//		//strcpy(info, "name:%csex:%c\tage:%d", "huanglei", "male", ageResult.pAgeResultArray[i]);
//		cv::putText(frame, info, CvPoint(FaceRes->rcFace[i].left, FaceRes->rcFace[i].bottom), cv::FONT_HERSHEY_COMPLEX, 0.6, cv::Scalar(255, 0, 0));
//	}
//}
//else
//{
//	//fprintf(stderr, "Face Detection failed, error code: %d\r\n", nRet);
//}
//
//cv::imshow("video", frame);


	///* 临时变量 获得本地脸部模型*/
	//ASVLOFFSCREEN offInput1 = { 0 };
	//offInput1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	//offInput1.ppu8Plane[0] = nullptr;
	//readBMP("photo1.bmp", (uint8_t**)&offInput1.ppu8Plane[0], &offInput1.i32Width, &offInput1.i32Height);
	//if (!offInput1.ppu8Plane[0])
	//{
	//	fprintf(stderr, "fail to ReadBmp(%s)\r\n", "photo1.bmp");
	//	return -1;
	//}
	//offInput1.pi32Pitch[0] = offInput1.i32Width * 3;
	//
	//LPAFD_FSDK_FACERES localFaceRes1 = nullptr;
	//AFR_FSDK_FACEINPUT localFaceResult;
	//fdEngine.FaceDetection(&offInput1, &localFaceRes1);
	//localFaceResult.lOrient = *(localFaceRes1->lfaceOrient);
	//localFaceResult.rcFace = *(localFaceRes1->rcFace);	
	//localFaceResult.lOrient = *(localFaceRes1->lfaceOrient);
	//localFaceResult.rcFace = *(localFaceRes1->rcFace);
	//AFR_FSDK_FACEMODEL localFaceModels1 = { 0 };
	//AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };

	//nRet = frEngine.ExtractFRFeature(&offInput1, &localFaceResult, &LocalFaceModels);
	//if (nRet != MOK)
	//{
	//	fprintf(stderr, "fail to Extract 1st FR Feature, errorcode: %d\r\n", nRet);
	//}
	//localFaceModels1.lFeatureSize = LocalFaceModels.lFeatureSize;
	//localFaceModels1.pbFeature = (MByte*)malloc(localFaceModels1.lFeatureSize);
	//memcpy(localFaceModels1.pbFeature, LocalFaceModels.pbFeature, localFaceModels1.lFeatureSize);

	//AFR_FSDK_FACEINPUT tempFaceResult;
	//AFR_FSDK_FACEMODEL tempFaceModels = { 0 };
	//MFloat  fSimilScore = 0.0f;