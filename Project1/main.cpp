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

using namespace cv;
using namespace std;

int main() {

	/* 声明engine */
	MRESULT nRet = MERR_UNKNOWN;
	FTEngine ft;
	AgeEngine ageEngine;
	GenderEngine genderEngine;
	FREngine frEngine;
	FDEngine fdEngine;

	/* engines 初始化 */
	nRet = ft.init();
	if (nRet != MOK)
	{
		fprintf(stderr, "Initial ftEngine failed, errorcode is %d \r\n", nRet);
		return -1;
	}
	nRet = ageEngine.init();
	if (MOK != nRet) {
		fprintf(stderr, "Initial ageEngine failed, errorcode is %d \r\n", nRet);
		return -1;
	}
	nRet = genderEngine.init();
	if (MOK != nRet) {
		fprintf(stderr, "Initial genderEngine failed, errorcode is %d \r\n", nRet);
		return -1;
	}
	nRet = frEngine.init();
	if (MOK != nRet) {
		fprintf(stderr, "Initial frEngine failed, errorcode is %d \r\n", nRet);
		return -1;
	}
	nRet = fdEngine.init();
	if (MOK != nRet) {
		fprintf(stderr, "Initial fdEngine failed, errorcode is %d \r\n", nRet);
		return -1;
	}


	/* 摄像头图像相关声明 */
	VideoCapture capture(0);
	if (!capture.isOpened())
	{
		return -1;
	}
	Mat frame;
	Mat show;
	
	/* 摄像头宽高FPS （像素为单位） */
	const int CAP_WIDTH = capture.get(CV_CAP_PROP_FRAME_WIDTH);
	const int CAP_HEIGHT = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
	const double CAP_FPS = capture.get(CV_CAP_PROP_FPS);

	/* 声明检测到结果用结构体 */
	LPAFT_FSDK_FACERES FaceRes = nullptr;
	ASVLOFFSCREEN offInput = { 0 };
	offInput.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	offInput.ppu8Plane[0] = nullptr;
	//cout << "flag1" << endl;

	/* 声明性别评估输入（FaceRes） */
	ASGE_FSDK_GENDERFACEINPUT genderFaceInput = { 0 };
	genderFaceInput.lFaceNumber = 0;

	/* 这里不分配内存，使用FaceTracking获得的结果FaceRes转化到GenderFaceInput */
	//genderFaceInput.pFaceRectArray = (MRECT *)malloc(sizeof(MRECT)*ARC_GENDER_MAX_FACE_NUM);
	//genderFaceInput.pFaceOrientArray = (MInt32 *)malloc(sizeof(MInt32)*ARC_GENDER_MAX_FACE_NUM);

	/* 性别评估中用到的frame或者图像参数，直接用了前面的内容 */
	//ASVLOFFSCREEN offScreenIn = { 0 }; // image data, replaced with your data
	//offScreenIn.u32PixelArrayFormat = ASVL_PAF_NV12; // image format
	//offScreenIn.i32Width = CAP_WIDTH; // image width
	//offScreenIn.i32Height = CAP_HEIGHT; // image height
	//offScreenIn.pi32Pitch[0] = offScreenIn.i32Width; // pitch of plane 0, may not be equal to width
	//offScreenIn.pi32Pitch[1] = offScreenIn.i32Width; // pitch of plane 1, may not be equal to width
	//offScreenIn.ppu8Plane[0] = MNull; // data address of plane 0
	//offScreenIn.ppu8Plane[1] = MNull; // data address of plane 1

	/* 单张图片性别估计用到的参数？ */
	//genderFaceInput.lFaceNumber = 1; // set face number from face detection or face tracking result

	/* 性别估计输出结构体 */
	ASGE_FSDK_GENDERRESULT genderResult = { 0 };

	/* 年龄估计输入输出结构体 */
	ASAE_FSDK_AGEFACEINPUT ageFaceInput = { 0 };
	//ageFaceInput.lFaceNumber = 0;
	//ageFaceInput.pFaceRectArray = (MRECT *)MMemAlloc(MNull, sizeof(MRECT)*ARC_AGE_MAX_FACE_NUM);
	//ageFaceInput.pFaceOrientArray = (MInt32 *)MMemAlloc(MNull, sizeof(MInt32)*ARC_AGE_MAX_FACE_NUM);
	ASAE_FSDK_AGERESULT ageResult = { 0 };

	ASVLOFFSCREEN offInput1 = { 0 };
	offInput1.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	offInput1.ppu8Plane[0] = nullptr;
	readBMP("photo1.bmp", (uint8_t**)&offInput1.ppu8Plane[0], &offInput1.i32Width, &offInput1.i32Height);
	if (!offInput1.ppu8Plane[0])
	{
		fprintf(stderr, "fail to ReadBmp(%s)\r\n", "photo1.bmp");
		return -1;
	}
	offInput1.pi32Pitch[0] = offInput1.i32Width * 3;
	
	LPAFD_FSDK_FACERES localFaceRes1 = nullptr;
	AFR_FSDK_FACEINPUT localFaceResult;
	fdEngine.FaceDetection(&offInput1, &localFaceRes1);
	localFaceResult.lOrient = *(localFaceRes1->lfaceOrient);
	localFaceResult.rcFace = *(localFaceRes1->rcFace);
	AFR_FSDK_FACEMODEL localFaceModels1 = { 0 };
	AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };

	nRet = frEngine.ExtractFRFeature(&offInput1, &localFaceResult, &LocalFaceModels);
	if (nRet != MOK)
	{
		fprintf(stderr, "fail to Extract 1st FR Feature, errorcode: %d\r\n", nRet);
	}
	localFaceModels1.lFeatureSize = LocalFaceModels.lFeatureSize;
	localFaceModels1.pbFeature = (MByte*)malloc(localFaceModels1.lFeatureSize);
	memcpy(localFaceModels1.pbFeature, LocalFaceModels.pbFeature, localFaceModels1.lFeatureSize);

	AFR_FSDK_FACEINPUT tempFaceResult;
	AFR_FSDK_FACEMODEL tempFaceModels = { 0 };
	MFloat  fSimilScore = 0.0f;
	
	/* 主功能实现 */
	while (true)
	{
		capture >> frame;
		imwrite("temp.bmp", frame);
		waitKey(20);
		
		//cout << "flag2" << endl;

		readBMP(INPUT_IMAGE_PATH, (uint8_t**)&offInput.ppu8Plane[0], &offInput.i32Width, &offInput.i32Height);
		if (!offInput.ppu8Plane[0]){
			fprintf(stderr, "fail to ReadBmp(%s)\r\n", INPUT_IMAGE_PATH);
			ft.uninit();
			return -1;
		}
		else{
			//fprintf(stdout, "Picture width : %d , height : %d \r\n", offInput.i32Width, offInput.i32Height);
		}
		offInput.pi32Pitch[0] = offInput.i32Width * 3;

		//cout << "flag3" << endl;

		show = imread("temp.bmp");

		nRet = ft.FaceTracking(&offInput, &FaceRes);

		/* 获得性别评估输入 FaceRes */
		//genderFaceInput 与 FaceResult 类型可转换
		genderFaceInput.lFaceNumber = FaceRes->nFace;
		genderFaceInput.pFaceRectArray = FaceRes->rcFace;
		genderFaceInput.pFaceOrientArray = &(FaceRes->lfaceOrient);

		/* 获得年龄评估输入 */
		ageFaceInput.lFaceNumber = FaceRes->nFace;
		ageFaceInput.pFaceOrientArray = &FaceRes->lfaceOrient;
		ageFaceInput.pFaceRectArray = FaceRes->rcFace;
		
		/* 获得对比输入 */
		tempFaceResult.lOrient = FaceRes->lfaceOrient;
		tempFaceResult.rcFace = *(FaceRes->rcFace);

		//获得genderResult
		genderEngine.GenderEstimationPreview(&offInput, &genderFaceInput, &genderResult);
		ageEngine.AgeEstimationPreview(&offInput, &ageFaceInput, &ageResult);
		
		AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };
		nRet = frEngine.ExtractFRFeature(&offInput, &tempFaceResult, &LocalFaceModels);
		if (nRet != MOK)
		{
			fprintf(stderr, "fail to Extract 2nd FR Feature, error code: %d\r\n", nRet);
		}
		tempFaceModels.lFeatureSize = LocalFaceModels.lFeatureSize;
		tempFaceModels.pbFeature = (MByte*)malloc(tempFaceModels.lFeatureSize);
		memcpy(tempFaceModels.pbFeature, LocalFaceModels.pbFeature, tempFaceModels.lFeatureSize);

		nRet = frEngine.FacePairMatching(&localFaceModels1, &tempFaceModels, &fSimilScore);
		if (nRet == MOK)
		{
			fprintf(stdout, "fSimilScore =  %f\r\n", fSimilScore);
		}
		else {
			fprintf(stderr, "FacePairMatching failed , errorcode is %d \r\n", nRet);
		}


		if (nRet == MOK)
		{
			//fprintf(stdout, "The number of face: %d\r\n", FaceRes->nFace);
			for (int i = 0; i < FaceRes->nFace; ++i)
			{
				/* 检测人脸矩形框&获得FaceRes */
				//fprintf(stdout, "Face[%d]:rect[%d, %d, %d, %d]\r\n", i, FaceRes->rcFace[i].left, FaceRes->rcFace[i].top, FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom);
				//cvRectangle(&show, CvPoint(FaceRes->rcFace[i].left, FaceRes->rcFace[i].top), CvPoint(FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom), CvScalar(255, 0, 0), 2);
				cv::rectangle(show, CvPoint(FaceRes->rcFace[i].left, FaceRes->rcFace[i].top), CvPoint(FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom), CvScalar(255, 0, 0), 2);
				cout << "性别\t" << genderResult.pGenderResultArray[i]<< "年龄:\t" << ageResult.pAgeResultArray[i] << endl;
				
			}
		}
		else
		{
			fprintf(stderr, "Face Detection failed, error code: %d\r\n", nRet);
		}
		
		cv::imshow("video", show);

		if (waitKey(50) >= 0)
		{
			break;
		}

		/* Very important */
		free(offInput.ppu8Plane[0]);
		free(tempFaceModels.pbFeature);
	}
	
	capture.release();
	//waitKey(1000);
	return 0;
}

