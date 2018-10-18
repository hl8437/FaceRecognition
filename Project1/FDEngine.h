#pragma once

#include "merror.h"
#include "arcsoft_fsdk_face_detection.h"
#include "const.h"
#include <stdlib.h>

class FDEngine
{
private:
	MInt32 nScale;
	MInt32 nMaxFace;
	MByte *pWorkMem;
	MHandle hEngine;
public:
	FDEngine();
	~FDEngine();
	int init();
	int uninit();
	int FaceDetection(LPASVLOFFSCREEN pImageData, LPAFD_FSDK_FACERES *pFaceRes);
};

