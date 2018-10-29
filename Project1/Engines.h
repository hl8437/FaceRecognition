#pragma once

#include <stdlib.h>
#include <iostream>

#include "AgeEngine.h"
#include "FDEngine.h"
#include "FREngine.h"
#include "FTEngine.h"
#include "GenderEngine.h"
#include "ReadBMP.h"

#include <opencv.hpp>

class Engines
{
protected:
	FDEngine*				mFDEngine;
	FTEngine*				mFTEngine;
	FREngine*				mFREngine;
	AgeEngine*				mAgeEngine;
	AgeEngine*				mAgeEngineForVideo;
	GenderEngine*			mGenderEngine;
	GenderEngine*			mGenderEngineForVideo;

	cv::VideoCapture mCapture;		// 摄像头
	int CAP_WIDTH;				// 摄像头宽度
	int CAP_HEIGHT;				// 摄像头高度
	cv::Mat* mFrame;				// 帧结构？
	

	ASVLOFFSCREEN mOffInput;						// engines图像输入
	LPAFT_FSDK_FACERES mFaceRes;					// 人脸检测结果
	ASGE_FSDK_GENDERFACEINPUT mGenderFaceInput;		// gender engine 输入
	ASGE_FSDK_GENDERRESULT mGenderResult;			// gender engine 输出
	ASAE_FSDK_AGEFACEINPUT mAgeFaceInput;			// ageengine 输入
	ASAE_FSDK_AGERESULT mAgeResult;					// ageEngine 输出

	/* 对于是否需要建立数组，或者分配内存，未知*/
	AFR_FSDK_FACEINPUT mFRFaceInput;				// FREngine 输入
	AFR_FSDK_FACEMODEL mFRFaceModel;				// FREngine 提取结果

	AFR_FSDK_FACEMODEL LocalFaceModels;				// 预设置为本地人脸模型队列

	AFR_FSDK_FACEMODEL videoFaceModels;				// 从视频提取的人脸模型

	MFloat tempFimiliar;			// 人脸比对相似度


	MRESULT faceTrackingRet;		// 检测人脸函数返回值
	MRESULT extractFRFeatureRet;	// 模型提取返回值
	MRESULT facePairMatchingRet;	// 人脸比对返回值

public:
	Engines();
	~Engines();
	int enginesInit();			// 初始化引擎
	int enginesClose();			// 释放引擎
	
	int initFaceVariables();		// 初始化人脸检测相关变量
	int initCamera();				// 打开摄像头,获取摄像宽高,初始化mFrame
	int initRet();

	int cameraToOffInput();			// mCapture -> mFrame -> offinput
	MRESULT faceTracking();			// 跟踪人脸信息, 并将结果输入至mFaceRes
	void getGenderFaceInput();		// 用mFaceRes初始化mGenderFaceInput
	void getAgeFaceInput();

	/* 对于FaceRes包含多张人脸的结果，效果未确定 */
	void getFRFaceInput();

	MRESULT extractFRFeature();

	int getFaceModelFromBMP();
	int getVideoFaceModel();

	int faceRecognitionOneToOne();

	
	void drawFaceRect();			// 人脸框绘制函数

	void showVideo();				// 视频显示


};

