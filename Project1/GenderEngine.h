#pragma once
#include "const.h"
#include "merror.h"
#include "arcsoft_fsdk_gender_estimation.h"
#include <stdlib.h>


class GenderEngine
{
private:
	MByte *pWorkMem;
	MHandle hEngine;
public:
	GenderEngine();
	~GenderEngine();
	int init();
	int uninit();
	int GenderEstimationStaticImage(LPASVLOFFSCREEN pImgInfo, LPASGE_FSDK_GENDERFACEINPUT pFaceRes, LPASGE_FSDK_GENDERRESULT pAgeRes);
	int GenderEstimationPreview(LPASVLOFFSCREEN pImgInfo, LPASGE_FSDK_GENDERFACEINPUT pFaceRes, LPASGE_FSDK_GENDERRESULT pAgeRes);
};