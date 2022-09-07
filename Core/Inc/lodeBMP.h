#ifndef __BMP
#define __BMP
#include "ws2812.h"
#include "SDCard.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma pack(2)//���ýṹ����뷽ʽ���ı�ᵼ�¶�ȡ����

// �ļ���Ϣͷ�ṹ��
typedef struct tagBITMAPFILEHEADER{
    unsigned short bfType;        //��Ϊ"BM"
    unsigned int   bfSize;        //�ļ��ֽ���(2-5)
    unsigned int bfReserved;    //λͼ�ļ������֣���Ϊ0(6-9)
    unsigned int   bfOffBits;   //��������ƫ�� (10-13)
} bmpHeader;

#define uint unsigned int
#define ushort unsigned short
//ͼ����Ϣͷ�ṹ��
/**
-------------------------------------------------------------------------------------------
| ƫ���� | ��С��λԪ�飩 |                             ��;                             	|
| :----: | :------------: | :----------------------------------------------------------: 	|
|  0Eh   |       4        |                   ��ͷ�ṹ�Ĵ�С��40�ֽڣ�                   	|
|  12h   |       4        |              λͼ��ȣ���λΪ���أ��з���������              		|
|  16h   |       4        |              λͼ�߶ȣ���λΪ���أ��з���������              		|
|  1Ah   |       2        |                  ɫ��ƽ������ֻ��1Ϊ��Чֵ                   	|
|  1Ch   |       2        | ÿ��������ռλ������ͼ���[ɫ��]������ֵΪ1��4��8��16��24��32 	|
|  1Eh   |       4        |               ��ʹ�õ�ѹ����������ȡֵ���±�               	|
|  22h   |       4        | ͼ���С��ָԭʼλͼ���ݵĴ�С�����ļ���С����ͬһ����� 			|
|  26h   |       4        |        ͼ��ĺ���ֱ��ʣ���λΪ����ÿ�ף��з���������        		|
|  2Ah   |       4        |        ͼ�������ֱ��ʣ���λΪ����ÿ�ף��з���������        		|
|  2Eh   |       4        |       ��ɫ�����ɫ����Ϊ0ʱ��ʾ��ɫ��ΪĬ�ϵ�2*ɫ��*��       		|
|  32h   |       4        |   ��Ҫ��ɫ����Ϊ0ʱ��ʾ������ɫ������Ҫ�ģ�ͨ����ʹ�ñ���    		|
-------------------------------------------------------------------------------------------
	*/
typedef struct tagBITMAPINFOHEADER{
    uint    biSize;          // �ṹ��ߴ� (14-17)
    int     biWidth;         // ͼ����  (18-21)
    int     biHeight;        // ͼ��߶�  (22-25)
    ushort  biPlanes;        // Ŀ���豸�ļ���Ϊ1(26-27)
    ushort  biBitCount;      // ����λ����Ϊ1��4��8��24(28-29)
    uint    biCompression;   // λͼѹ�����ͣ�0Ϊ��ѹ����1ΪBI_RLE8��2ΪBI_RLE4(30-33)
    uint    biSizeImage;     // ���������ݴ�С,����bfSize-bfOffBits (34-37)
    int     biXPelsPerMeter; // ˮƽ�ֱ��ʣ�һ��Ϊ0 (38-41)
    int     biYPelsPerMeter; // ��ֱ�ֱ��ʣ�һ��Ϊ0 (42-45)
    uint    biClrUsed;       // λͼ��ɫ���е���ɫ����0��ʾʹ�����е�ɫ����(46-49)
    uint    biClrImportant;  // ��Ҫ��ɫ��������Ŀ��0��ʾ����Ҫ(50-53)
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
