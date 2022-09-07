#ifndef __menu_h
#define __menu_h

#include "OLED.h"
#include "main.h"
#include "ws2812.h"
#include "dma.h"
#include "sdio.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

#define min_start 9
#define max_start 64

#define getName(var) #var

typedef enum
{
	printer,
	saber
}WorkModeType;

typedef enum
{
	_Saber,
	_Printer,
	_Setting,
}menu;

typedef enum
{
	L1 = 0,
	L2 = 1,
	L3 = 2,
	L4 = 3
} brightness_State;

extern brightness_State brightness;

extern WorkModeType WorkMode;

extern saberType WorkSaberType;

extern uint8_t printerFlag;

extern char saberName[80];

extern char imageName[80];

void ModeMenu(void);

#endif
