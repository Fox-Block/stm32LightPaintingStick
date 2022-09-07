#include "ws2812.h"
#include "menu.h"

const RGBColor_TypeDef _RED      = {0xFF	,	0		,0		};
const RGBColor_TypeDef _GREEN    = {0  	, 0xFF,0		};
const RGBColor_TypeDef _BLUE     = {0		,  0	,0xFF	};
const RGBColor_TypeDef _YELLOW   = {0xFF	, 0xFF,0		};
const RGBColor_TypeDef _MAGENTA  = {0xFF	,  0	,0xFF	};
const RGBColor_TypeDef _BLACK    = {0		,  0	,0		};
const RGBColor_TypeDef _WHITE    = {0xFF	, 0xFF,0xFF	};

const char saberNamelist[numOfsaberType][8] = {"run1","run2","run3","pl1","pl2","pl3","pl4","pl5","RED","GREEN","BLUE","YELLOW","MAGENTA","BLACK","WHITE"};

//bit:0xC0  0,0xF8  1
const uint8_t code[]={0xC0,0xF8};

RGBColor_TypeDef RGB_DAT[LED_NUM];

uint32_t delayTime = 0; 



extern DMA_HandleTypeDef hdma_spi1_tx;


int fputc(int ch, FILE *f)
{
	HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}
int fgetc(FILE *f)
{	
	int ch;
	HAL_UART_Receive(&huart1, (uint8_t *)&ch, 1, 1000);	
	return (ch);
}


static void SPI_Send(uint8_t *SPI_RGB_BUFFER)
{
	while(HAL_DMA_GetState(&hdma_spi1_tx) != HAL_DMA_STATE_READY);
	HAL_SPI_Transmit_DMA(&hspi1,SPI_RGB_BUFFER,24*LED_NUM*2);  
}

void RGB_Set_Color(uint8_t LedId, RGBColor_TypeDef Color)  
{
  if(LedId < LED_NUM)
	{
		RGB_DAT[LedId].G = Color.G;
		RGB_DAT[LedId].R = Color.R;
		RGB_DAT[LedId].B = Color.B;
	}
}

void RGB_Reflash(void)
{
	static uint8_t RGB_BUFFER[2*24*LED_NUM]={0};
	uint8_t dat_b,dat_r,dat_g;
	//RESET
	{
		for(int i=0;i<LED_NUM;i++)
		{
			dat_g = 0;
			dat_r = 0;
			dat_b = 0;
			for(int j=0;j<8;j++)
			{
				RGB_BUFFER[7- j + i * 24] = 0;
				RGB_BUFFER[15-j + i * 24] = 0;
				RGB_BUFFER[23-j + i * 24] = 0;
			}
		}	
		//color data
		for(int i=0;i<LED_NUM;i++)
		{
			dat_g = RGB_DAT[i].G << brightness;
			dat_r = RGB_DAT[i].R << brightness;
			dat_b = RGB_DAT[i].B << brightness;
			
			for(int j=0;j<8;j++)
			{
				RGB_BUFFER[24*LED_NUM + 7 -j + i * 24] = code[dat_g & 0x01];
				RGB_BUFFER[24*LED_NUM + 15-j + i * 24] = code[dat_r & 0x01];
				RGB_BUFFER[24*LED_NUM + 23-j + i * 24] = code[dat_b & 0x01];
				dat_g >>=1;
				dat_r >>=1;
				dat_b >>=1;
			}
		}
		
		SPI_Send(RGB_BUFFER);
	}
}

void RGB_RST(void)
{
	uint8_t dat[100] = {0};
	while(HAL_DMA_GetState(&hdma_spi1_tx) != HAL_DMA_STATE_READY);
  /* RGB RESET */
	HAL_SPI_Transmit_DMA(&hspi1,dat,100); 
	HAL_Delay(10);
}


void RGB_Contorl_0(void)
{
	static uint8_t counter = 0;
	for(uint8_t i=0;i<LED_NUM;i++)
	{ 
    if(i-counter<3 && i-counter>-3)
		{
			RGB_Set_Color(i,_WHITE);
			
		}
		else
		{
			if(i%4 == 3)RGB_Set_Color(i,_RED);
			else RGB_Set_Color(i,_BLUE);
		} 
	}
		counter++;
	if(counter == LED_NUM)counter =0;
	RGB_Reflash();
}

void RGB_Contorl_1(void)
{
	static uint8_t counter = 0;
	RGBColor_TypeDef color = _BLUE;
	uint8_t increase = LED_NUM/2/256;
	for(uint8_t i=0;i<LED_NUM;i++)
	{ 
    if(i-counter<8 && i-counter>-8)
		{
			RGB_Set_Color(i,_WHITE);
			
		}
		else
		{
			color.G += increase;
			color.R += increase;
			RGB_Set_Color(i,color);
		} 
	}
		counter++;
	if(counter == LED_NUM)counter =0;
	RGB_Reflash();
}

 void RGB_Contorl_2(void)
{
	static uint8_t counter = 0;
	RGBColor_TypeDef color = _RED;
	uint8_t increase = LED_NUM/2/256;
	for(uint8_t i=0;i<LED_NUM;i++)
	{ 
    if((i-counter < 4 && i-counter > -4) ||\
			(LED_NUM - i - counter < 4 && LED_NUM - i - counter > -4))
		{
			RGB_Set_Color(i,_WHITE);
			
		}
		else
		{
			color.G += increase;
			color.R += increase;
			RGB_Set_Color(i,color);
		} 
	}
		counter++;
	if(counter == LED_NUM)counter =0;
	RGB_Reflash();
}

void RGB_Color(saberType colorIn)
{
	static uint8_t counter = 0;
	RGBColor_TypeDef color;
	switch(colorIn)
	{
		case RED:
		{
			color = _RED;
			break;
		}
		case GREEN:
		{
			color = _GREEN;
			break;
		}	
		case BLUE:
		{
			color = _BLUE;
			break;
		}
		case YELLOW:
		{
			color = _YELLOW;
			break;
		}
		case MAGENTA:
		{
			color = _MAGENTA;
			break;
		}
		case BLACK:
		{
			color = _BLACK;
			break;
		}
		case WHITE:
		{
			color = _WHITE;
			break;
		}
		default:
			color = _WHITE;
			break;
	}
	for(uint8_t i=0;i<LED_NUM;i++)
	{ 
			RGB_Set_Color(i,color);
	}
		counter++;
	if(counter == LED_NUM)counter =0;
	
	RGB_Reflash();
}

void lightContorl(void)
{
	static uint8_t counter = 0;
	RGBColor_TypeDef color;
	for(int j = 0;j< LED_NUM;j++)
	{
		
		color.B = j % (counter++);
		color.G = j*LED_NUM/256;
		color.R = 256-j*LED_NUM/256;
		RGB_DAT[j] = color;
	}
	counter++;
	RGB_Reflash();
}
