#ifndef __WS2812_H
#define __WS2812_H

#include "main.h"
#include <stdio.h>
#include "spi.h"
#include "dma.h"
#include "usart.h"
#include "SDCard.h"


#pragma pack(1)

#define numOfimage 5
#define numOfsaberType 15
#define maxBrightness 4

#define LED_NUM    144	// RGB数量

typedef struct				//颜色结构体
{
  uint8_t R;
  uint8_t G;
  uint8_t B;
}RGBColor_TypeDef;

typedef enum
{
	run1,
	run2,
	run3,
	pl1,
	pl2,
	pl3,
	pl4,
	pl5,
	RED,
	GREEN,
	BLUE,
	YELLOW,
	MAGENTA,
	BLACK,
	WHITE
}saberType;



extern RGBColor_TypeDef RGB_DAT[LED_NUM];
extern uint32_t delayTime; //控制SPI刷新速度
extern const char saberNamelist[numOfsaberType][8];

// 复位函数
void RGB_RST(void);
// 颜色设置函数
void RGB_Set_Color(uint8_t LedId, RGBColor_TypeDef Color);
// RGB 刷新函数
void RGB_Reflash(void);
// 图像展示函数
void Show_image(unsigned int length,uint32_t speed);
// 颜色测试
void RGB_Contorl_0(void);
void RGB_Contorl_1(void);
void RGB_Contorl_2(void);
void lightContorl(void);

void RGB_Color(saberType colorIn);

#endif /* __WS2812_H */
