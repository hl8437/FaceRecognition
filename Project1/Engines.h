#pragma once

#include <stdlib.h>
#include <iostream>

#include "AgeEngine.h"
#include "FDEngine.h"
#include "FREngine.h"
#include "FTEngine.h"
#include "GenderEngine.h"

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
public:
	Engines();
	~Engines();
	int enginesInit();
	int enginesClose();
};

