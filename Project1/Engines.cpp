#include "Engines.h"

using namespace std;

Engines::Engines()
{
}

Engines::~Engines()
{
}

int Engines::enginesInit()
{
	// ��ʼ������
	MRESULT ret = MERR_UNKNOWN;

	// ��ʼ��FDE
	mFDEngine = new FDEngine();
	ret = mFDEngine->init();
	if (ret != MOK)
	{
		cout << "��ʼ��FD����ʧ��,������: %d, ���򽫹رգ�" << endl;
		enginesClose();
		return ret;
	}

	// ��ʼ��FTE
	mFTEngine = new FTEngine();
	ret = mFTEngine->init();
	if (ret != MOK)
	{
		cout << "��ʼ��FT����ʧ��,������: %d, ���򽫹رգ�" << endl;
		enginesClose();
		return ret;
	}

	mFREngine = new FREngine();
	ret = mFREngine->init();
	if (ret != MOK)
	{
		cout << "��ʼ��FD����ʧ��,������: %d, ���򽫹رգ�" << endl;
		enginesClose();
		return ret;
	}
	mAgeEngine = new AgeEngine();
	ret = mAgeEngine->init();
	if (ret != MOK)
	{
		cout << "��ʼ��FD����ʧ��,������: %d, ���򽫹رգ�" << endl;
		enginesClose();
		return ret;
	}
	mGenderEngine = new GenderEngine();
	ret = mGenderEngine->init();
	if (ret != MOK)
	{
		cout << "��ʼ��FD����ʧ��,������: %d, ���򽫹رգ�" << endl;
		enginesClose();
		return ret;
	}
	return ret;

}

int Engines::enginesClose()
{
	// ֹͣ���в��ͷ��ڴ������
	//Stop();
	if (mFDEngine != nullptr)
	{
		mFDEngine->uninit();
		delete mFDEngine;
		mFDEngine = nullptr;
	}
	if (mFREngine != nullptr)
	{
		mFREngine->uninit();
		delete mFREngine;
		mFREngine = nullptr;
	}
	if (mAgeEngine != nullptr)
	{
		mAgeEngine->uninit();
		delete mAgeEngine;
		mAgeEngine = nullptr;
	}
	if (mGenderEngine != nullptr)
	{
		mGenderEngine->uninit();
		delete mGenderEngine;
		mGenderEngine = nullptr;
	}


	exit(0);
	return -1;

}

int Engines::initFaceVariables()
{
	/* engine ��Ƶ���� */
	mOffInput = { 0 };
	mOffInput.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;	//TODO
	mOffInput.ppu8Plane[0] = nullptr;

	/* ��������� */
	mFaceRes = nullptr;

	/* gender engine ���� */
	mGenderFaceInput = { 0 };
	mGenderFaceInput.lFaceNumber = 0;

	/* gender engine ��� */
	mGenderResult = { 0 };

	/* ageengine ���� */
	mAgeFaceInput = { 0 };

	/* ageEngine ���*/
	mAgeResult = { 0 };

	/* FREngine ���� */
	//mRecognitionFaceInput = 

	/* FREngine ��ȡ��ģ�� */
	mFRFaceModel = { 0 };

	return 0;
}

int Engines::initCamera()
{
	mCapture.open(0);
	if (!mCapture.isOpened())
	{
		cout << "����ͷδ��" << endl;
		return -1;
	}

	int CAP_WIDTH = mCapture.get(CV_CAP_PROP_FRAME_WIDTH);
	int CAP_HEIGHT = mCapture.get(CV_CAP_PROP_FRAME_HEIGHT);

	mFrame = new cv::Mat(CAP_HEIGHT, CAP_WIDTH, CV_8UC3);

	return 0;
}

int Engines::initRet()
{
	faceTrackingRet = MERR_UNKNOWN;
	extractFRFeatureRet = MERR_UNKNOWN;
	return 0;
}

int Engines::cameraToOffInput()
{
	mCapture >> *mFrame;
	mOffInput.u32PixelArrayFormat = ASVL_PAF_RGB24_B8G8R8;
	mOffInput.i32Width = mFrame->cols;
	mOffInput.i32Height = mFrame->rows;
	mOffInput.ppu8Plane[0] = mFrame->data;
	mOffInput.pi32Pitch[0] = mOffInput.i32Width * 3;
	return 0;
}

MRESULT Engines::faceTracking()
{
	faceTrackingRet = mFTEngine->FaceTracking(&mOffInput, &mFaceRes);
	return faceTrackingRet;
}

void Engines::getGenderFaceInput()
{
	if (faceTrackingRet == MOK)
	{
		mGenderFaceInput.lFaceNumber = mFaceRes->nFace;
		mGenderFaceInput.pFaceRectArray = mFaceRes->rcFace;
		mGenderFaceInput.pFaceOrientArray = &(mFaceRes->lfaceOrient);
	}
}

void Engines::getAgeFaceInput()
{
	if (faceTrackingRet == MOK)
	{
		mAgeFaceInput.lFaceNumber = mFaceRes->nFace;
		mAgeFaceInput.pFaceOrientArray = &mFaceRes->lfaceOrient;
		mAgeFaceInput.pFaceRectArray = mFaceRes->rcFace;
	}
}

void Engines::getFRFaceInput()
{
	if (faceTrackingRet == MOK)
	{
		mFRFaceInput.lOrient = mFaceRes->lfaceOrient;
		mFRFaceInput.rcFace = *mFaceRes->rcFace;
	}
}

MRESULT Engines::extractFRFeature()
{
	extractFRFeatureRet = mFREngine->ExtractFRFeature(&mOffInput, &mFRFaceInput, &mFRFaceModel);
	return extractFRFeatureRet;
}

int Engines::getFaceInputFromBMP()
{
	///* ��ʱ���� ��ñ�������ģ��*/
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
	
	LPAFD_FSDK_FACERES localFaceRes = nullptr;
	AFR_FSDK_FACEINPUT localFRInput;
	mFDEngine->FaceDetection(&offInput1, &localFaceRes);
	localFRInput.lOrient = *(localFaceRes->lfaceOrient);
	localFRInput.rcFace = *(localFaceRes->rcFace);	
	localFRInput.lOrient = *(localFaceRes->lfaceOrient);
	localFRInput.rcFace = *(localFaceRes->rcFace);
	
	AFR_FSDK_FACEMODEL localFaceModel = { 0 };
	AFR_FSDK_FACEMODEL LocalFaceModels = { 0 };

	extractFRFeatureRet = mFREngine->ExtractFRFeature(&offInput1, &localFRInput, &localFaceModel);
	if (extractFRFeatureRet != MOK)
	{
		return extractFRFeatureRet;
	}
	LocalFaceModels.lFeatureSize = localFaceModel.lFeatureSize;
	LocalFaceModels.pbFeature = (MByte*)malloc(localFaceModel.lFeatureSize);
	memcpy(LocalFaceModels.pbFeature, localFaceModel.pbFeature, localFaceModel.lFeatureSize);

	//AFR_FSDK_FACEINPUT tempFaceResult;
	//AFR_FSDK_FACEMODEL tempFaceModels = { 0 };
	//MFloat  fSimilScore = 0.0f;
}

void Engines::drawFaceRect()
{
	if (faceTrackingRet == MOK)
	{
		for (int i = 0; i < mFaceRes->nFace; ++i)
		{
			//����Ƶ�ϻ�������
			cv::rectangle(*mFrame, CvPoint(mFaceRes->rcFace[i].left, mFaceRes->rcFace[i].top), CvPoint(mFaceRes->rcFace[i].right, mFaceRes->rcFace[i].bottom), CvScalar(255, 0, 0), 2);
					
		}
	}
//if (nRet == MOK)
//{
//	//fprintf(stdout, "The number of face: %d\r\n", FaceRes->nFace);
//	for (int i = 0; i < FaceRes->nFace; ++i)
//	{
//		//����Ƶ�ϻ�������
//		cv::rectangle(frame, CvPoint(FaceRes->rcFace[i].left, FaceRes->rcFace[i].top), CvPoint(FaceRes->rcFace[i].right, FaceRes->rcFace[i].bottom), CvScalar(255, 0, 0), 2);
//		
//		//�ھ��εײ���ӡ��Ϣ
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
}

void Engines::showVideo()
{
	drawFaceRect();
	cv::imshow("video", *mFrame);
}

