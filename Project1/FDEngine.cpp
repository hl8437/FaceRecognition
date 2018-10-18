
#include "FDEngine.h"


FDEngine::FDEngine()
{
	nScale = 16;
	nMaxFace = 12;
	pWorkMem = nullptr;
	hEngine = nullptr;
}


FDEngine::~FDEngine()
{
}


int FDEngine::init()
{
	pWorkMem = (MByte *)malloc(WORKBUF_SIZE_FD);
	if (pWorkMem == nullptr)
	{
		return -1;
	}
	int ret = AFD_FSDK_InitialFaceEngine(APPID, SDKKeyFD, pWorkMem, WORKBUF_SIZE_FD, &hEngine, AFD_FSDK_OPF_0_HIGHER_EXT, nScale, nMaxFace);
	return ret;
}


int FDEngine::uninit() {
	int ret = AFD_FSDK_UninitialFaceEngine(hEngine);
	if (pWorkMem != nullptr)
	{
		free(pWorkMem);
	}
	return ret;
}

int FDEngine::FaceDetection(LPASVLOFFSCREEN pImageData, LPAFD_FSDK_FACERES *pFaceRes)
{
	int ret = AFD_FSDK_StillImageFaceDetection(hEngine, pImageData, pFaceRes);
	return ret;
}