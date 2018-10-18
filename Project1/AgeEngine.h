#pragma once
#include "const.h"
#include "merror.h"
#include "arcsoft_fsdk_age_estimation.h"
#include <stdlib.h>


class AgeEngine
{
private:
	MByte *pWorkMem;
	MHandle hEngine;
public:
	AgeEngine();
	~AgeEngine();
	int init();
	int uninit();
	int AgeEstimationStaticImage(LPASVLOFFSCREEN pImgInfo, LPASAE_FSDK_AGEFACEINPUT pFaceRes, LPASAE_FSDK_AGERESULT pAgeRes);
	int AgeEstimationPreview(LPASVLOFFSCREEN pImgInfo, LPASAE_FSDK_AGEFACEINPUT pFaceRes, LPASAE_FSDK_AGERESULT pAgeRes);
};