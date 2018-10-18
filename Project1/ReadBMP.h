#pragma once

#include <stdint.h>
#include <stdio.h>
#include "merror.h"

bool readBMP(const char* path, uint8_t **imageData, int *pWidth, int *pHeight);
