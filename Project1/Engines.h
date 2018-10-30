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

	cv::VideoCapture mCapture;		// ����ͷ
	int CAP_WIDTH;				// ����ͷ���
	int CAP_HEIGHT;				// ����ͷ�߶�
	cv::Mat* mFrame;				// ֡�ṹ��
	
public:
	ASVLOFFSCREEN mOffInput;						// enginesͼ������
	LPAFT_FSDK_FACERES mFaceRes;					// ���������
	ASGE_FSDK_GENDERFACEINPUT mGenderFaceInput;		// gender engine ����
	ASGE_FSDK_GENDERRESULT mGenderResult;			// gender engine ���
	ASAE_FSDK_AGEFACEINPUT mAgeFaceInput;			// ageengine ����
	ASAE_FSDK_AGERESULT mAgeResult;					// ageEngine ���

	/* �����Ƿ���Ҫ�������飬���߷����ڴ棬δ֪*/
	AFR_FSDK_FACEINPUT mFRFaceInput;				// FREngine ����
	AFR_FSDK_FACEMODEL mFRFaceModel;				// FREngine ��ȡ���

	AFR_FSDK_FACEMODEL LocalFaceModels;				// Ԥ����Ϊ��������ģ�Ͷ���

	AFR_FSDK_FACEMODEL videoFaceModels;				// ����Ƶ��ȡ������ģ��

	MFloat tempFimiliar;			// �����ȶ����ƶ�


	MRESULT faceTrackingRet;		// ���������������ֵ
	MRESULT extractFRFeatureRet;	// ģ����ȡ����ֵ
	MRESULT facePairMatchingRet;	// �����ȶԷ���ֵ

public:
	Engines();
	~Engines();
	int enginesInit();			// ��ʼ������
	int enginesClose();			// �ͷ�����

	int initCamera();				// ������ͷ,��ȡ������,��ʼ��mFrame
	void releaseCamera();			// �ر�����ͷ

	int initRet();					// ��ʼ������ret
	int initFaceVariables();		// ��ʼ�����������ر���
	
	int cameraToOffInput();			// mCapture -> mFrame -> mOffinput
	MRESULT faceTracking();			// ����������Ϣ, ��OffInput����������������������mFaceRes
	void getGenderFaceInput();		// ��mFaceRes���mGenderFaceInput
	void getAgeFaceInput();			// ��mFaceRes���mAgeFaceInput
	/* ����FaceRes�������������Ľ����Ч��δȷ�� */
	void getFRFaceInput();			// ��mFaceRes���mFRFaceInput
	MRESULT extractFRFeature();		// ��mOffInput�Լ�mFaceRes����Model����mFRFaceModel
	AFR_FSDK_FACEMODEL getFaceModelFromBMP(const char* path);		// �ӱ���BMP��ȡModel���洢��LocalFaceModels
	int getVideoFaceModel();		// ��mOffInput��mFaceRes��ȡModel���洢��VideoFaceModel,ת����videoFaceModels
	int faceRecognitionOneToOne();	// ����Model�ıȶ�
	void drawFaceRect();			// ��������ƺ���

	void showVideo();				// ��Ƶ��ʾ


};

