#ifndef _LQOLED_H
#define _LQOLED_H
#include "stm32f4xx_hal.h"
#include "stdlib.h"
#include "main.h"

#include <stdio.h>
#include "spi.h"
#include "dma.h"
#include "usart.h"
#include "keyControl.h"
#include "SDCard.h"

//���ִ�С��Ӣ�����ִ�С
#define 	TYPE8X16		1
#define 	TYPE16X16		2
#define 	TYPE6X8			3

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

//-----------------OLED�˿ڶ���----------------  					   
#define OLED_DC_SET() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET);
#define OLED_DC_RST() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET);

#define OLED_RST_SET() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET);
#define OLED_RST_RST() HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET);

void OLED_Init(void);
void OLED_Display(void);
void OLED_Fill(uint8_t bmp_data);
void OLED_Set_Pixel(unsigned char x, unsigned char y,unsigned char color);

void GUI_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t Char_Size,uint8_t mode);
void GUI_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t Char_Size,uint8_t mode);

#endif

