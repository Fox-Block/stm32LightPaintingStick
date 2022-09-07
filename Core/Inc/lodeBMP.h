#ifndef __BMP
#define __BMP
#include "ws2812.h"
#include "SDCard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(2)//设置结构体对齐方式，改变会导致读取错误！

// 文件信息头结构体
typedef struct tagBITMAPFILEHEADER{
    unsigned short bfType;        //必为"BM"
    unsigned int   bfSize;        //文件字节数(2-5)
    unsigned int bfReserved;    //位图文件保留字，必为0(6-9)
    unsigned int   bfOffBits;   //像素数据偏移 (10-13)
} bmpHeader;

#define uint unsigned int
#define ushort unsigned short
//图像信息头结构体
/**
-------------------------------------------------------------------------------------------
| 偏移量 | 大小（位元组） |                             用途                             	|
| :----: | :------------: | :----------------------------------------------------------: 	|
|  0Eh   |       4        |                   该头结构的大小（40字节）                   	|
|  12h   |       4        |              位图宽度，单位为像素（有符号整数）              		|
|  16h   |       4        |              位图高度，单位为像素（有符号整数）              		|
|  1Ah   |       2        |                  色彩平面数；只有1为有效值                   	|
|  1Ch   |       2        | 每个像素所占位数，即图像的[色深]。典型值为1、4、8、16、24和32 	|
|  1Eh   |       4        |               所使用的压缩方法，可取值见下表。               	|
|  22h   |       4        | 图像大小。指原始位图数据的大小，与文件大小不是同一个概念。 			|
|  26h   |       4        |        图像的横向分辨率，单位为像素每米（有符号整数）        		|
|  2Ah   |       4        |        图像的纵向分辨率，单位为像素每米（有符号整数）        		|
|  2Eh   |       4        |       调色板的颜色数，为0时表示颜色数为默认的2*色深*个       		|
|  32h   |       4        |   重要颜色数，为0时表示所有颜色都是重要的；通常不使用本项    		|
-------------------------------------------------------------------------------------------
	*/
typedef struct tagBITMAPINFOHEADER{
    uint    biSize;          // 结构体尺寸 (14-17)
    int     biWidth;         // 图像宽度  (18-21)
    int     biHeight;        // 图像高度  (22-25)
    ushort  biPlanes;        // 目标设备的级别，为1(26-27)
    ushort  biBitCount;      // 像素位数，为1、4、8或24(28-29)
    uint    biCompression;   // 位图压缩类型，0为不压缩、1为BI_RLE8、2为BI_RLE4(30-33)
    uint    biSizeImage;     // 单像素数据大小,等于bfSize-bfOffBits (34-37)
    int     biXPelsPerMeter; // 水平分辨率，一般为0 (38-41)
    int     biYPelsPerMeter; // 垂直分辨率，一般为0 (42-45)
    uint    biClrUsed;       // 位图颜色表中的颜色数，0表示使用所有调色板项(46-49)
    uint    biClrImportant;  // 重要颜色索引的数目，0表示都重要(50-53)
} infoHeader;

typedef struct tagImageInfo
{
	uint32_t width;
	uint32_t height;
}ImageInfo;


extern ImageInfo ImpInfo;

uint8_t ShowBMP(FIL* fp);
uint8_t ShowPL(FIL* fp);

#endif
