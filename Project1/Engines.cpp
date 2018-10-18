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
	// 初始化引擎
	int ret = 0;
	mFDEngine = new FDEngine();
	ret = mFDEngine->init();
	if (ret != MOK)
	{
		cout << "初始化FD引擎失败,错误码: %d, 程序将关闭！" << endl;
		enginesClose();
		return -1;
	}
	mFREngine = new FREngine();
	ret = mFREngine->init();
	if (ret != MOK)
	{
		cout << "初始化FD引擎失败,错误码: %d, 程序将关闭！" << endl;
		enginesClose();
		return -1;
	}
	mAgeEngine = new AgeEngine();
	ret = mAgeEngine->init();
	if (ret != MOK)
	{
		cout << "初始化FD引擎失败,错误码: %d, 程序将关闭！" << endl;
		enginesClose();
		return -1;
	}
	mGenderEngine = new GenderEngine();
	ret = mGenderEngine->init();
	if (ret != MOK)
	{
		cout << "初始化FD引擎失败,错误码: %d, 程序将关闭！" << endl;
		enginesClose();
		return -1;
	}
}

int Engines::enginesClose()
{
	// 停止运行并释放内存和引擎
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
	//for (std::vector<FACE*>::iterator iter = mFaceModels.begin(); iter != mFaceModels.end();)
	//{
	//	(*iter)->image.Destroy();
	//	delete[](*iter)->faceModel.pbFeature;
	//	delete (*iter);
	//	iter = mFaceModels.erase(iter);
	//}
	//if (mFTFaceResult.rcFace != nullptr)
	//{
	//	delete[] mFTFaceResult.rcFace;
	//	mFTFaceResult.rcFace = nullptr;
	//}
	//CloseHandle(hMutex);

	exit(0);
	return -1;

}
