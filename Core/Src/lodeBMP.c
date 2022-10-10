#include "lodeBMP.h"

ImageInfo ImpInfo;
uint8_t ShowBMP(FIL* fp)
{
		bmpHeader fileHeader;
		infoHeader infoHeader;
		unsigned int length;
		
		retSD = f_read(fp,&fileHeader, sizeof(fileHeader), &length);
		if(retSD != FR_OK)
		{
			while(1) printf("fail to read %d",retSD);
		}
		
		retSD = f_read(fp,&infoHeader, sizeof(infoHeader), &length);
		
		if(retSD != FR_OK)
		{
			while(1) printf("fail to read %d",retSD);
		}
		if (fileHeader.bfType != 19778)
		{
			printf("%s %d \n", "err 不是LED图片",fileHeader.bfType);
		}

	int x, y;
	int w = infoHeader.biWidth;
	int	h = infoHeader.biHeight;
	if(w!= LED_NUM)printf("Warning：LED数目与图片尺寸不匹配");
	RGBColor_TypeDef pixel;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < LED_NUM; x++)
		{
			f_read(fp,&pixel, sizeof(pixel), &length);
		  //获取RGB值，注意：存储顺序为GBR
			pixel.R = pixel.R + pixel.B;
			pixel.B = pixel.R - pixel.B;
			pixel.R = pixel.R -pixel.B;
			RGB_DAT[x] = pixel;
			//如果已经读完，则提前退出，但是如果设置正确，不应该运行到本语句
			if(length == 0)goto OUT;
		}
		/* send data to SPI device */
		RGB_Reflash();
	}
OUT:	
		for(uint8_t i=0;i<LED_NUM;i++)
	{ 
		//在打印完成后将颜色设置为黑色
			RGB_DAT[i].R = 0;
			RGB_DAT[i].G = 0;
			RGB_DAT[i].B = 0;
	}
	RGB_Reflash();
	
	return 0;
}
uint8_t ShowPL(FIL* fp)
{
		bmpHeader fileHeader;
		infoHeader infoHeader;
		unsigned int length;
		
		retSD = f_read(fp,&fileHeader, sizeof(fileHeader), &length);
		if(retSD != FR_OK)
		{
			while(1) printf("fail to read %d",retSD);
		}
		
		retSD = f_read(fp,&infoHeader, sizeof(infoHeader), &length);
		
		if(retSD != FR_OK)
		{
			while(1) printf("fail to read %d",retSD);
		}
		if (fileHeader.bfType != 19778)
		{
			printf("%s %d \n", "err 不是BMP文件",fileHeader.bfType);
		}

	int x, y;
	int w = infoHeader.biWidth;
	int	h = infoHeader.biHeight;
		if(w!= LED_NUM)printf("Warning：LED数目与图片尺寸不匹配");
	RGBColor_TypeDef pixel;
	for (y = 0; y < h; y++)
	{
		for (x = 0; x < LED_NUM; x++)
		{
			HAL_Delay(10);
			f_read(fp,&pixel, sizeof(pixel), &length);
			//交换R 与 B的位置
			pixel.R = pixel.R + pixel.B;
			pixel.B = pixel.R - pixel.B;
			pixel.R = pixel.R -pixel.B;
			RGB_DAT[x] = pixel;
		}
		/* send data to SPI device */
		RGB_Reflash();
	}
	return 0;
}
