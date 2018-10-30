#include "FREngine.h"
//Can you see me?---whb
FREngine::FREngine()
{
	pWorkMem = nullptr;
	hEngine = nullptr;
}
FREngine::~FREngine()
{
}
int FREngine::init()
{
	pWorkMem = (MByte *)malloc(WORKBUF_SIZE_FR);
	if (pWorkMem == nullptr)
	{
		return -1;
	}
	int ret = AFR_FSDK_InitialEngine(APPID, SDKKeyFR, pWorkMem, WORKBUF_SIZE_FR, &hEngine);
	return ret;
}
int FREngine::uninit()
{
	int ret = AFR_FSDK_UninitialEngine(hEngine);
	if (pWorkMem != nullptr)
	{
		free(pWorkMem);
	}
	return ret;
}
int FREngine::ExtractFRFeature(LPASVLOFFSCREEN pImgData, LPAFR_FSDK_FACEINPUT pFaceRes, LPAFR_FSDK_FACEMODEL pFaceModels)
{
	int ret = AFR_FSDK_ExtractFRFeature(hEngine, pImgData, pFaceRes, pFaceModels);
	return ret;
}
MRESULT FREngine::FacePairMatching(AFR_FSDK_FACEMODEL *reffeature, AFR_FSDK_FACEMODEL *probefeature, MFloat *pfSimilScore)
{
	MRESULT ret = AFR_FSDK_FacePairMatching(hEngine, reffeature, probefeature, pfSimilScore);
	return ret;
}
