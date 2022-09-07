#ifndef __SDCard_h
#define __SDCard_h

#include "main.h"
#include "dma.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"
#include "ws2812.h"
#include <stdio.h>
#include "ws2812.h"
#include "lodeBMP.h"

extern BYTE work[_MAX_SS];

void fileDecoder(char *fileName);

void patternDecoder(char *fileName);

void SDCardSetting(void);

#endif
