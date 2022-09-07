#include "SDCard.h"

BYTE work[_MAX_SS];

void SDCardSetting(void)
{
	retSD = f_mount(&SDFatFS,SDPath,1);
	switch(retSD)
	{
		case FR_NO_FILESYSTEM :
		{
			retSD = f_mkfs(SDPath,FM_FAT32,512,work,sizeof(work));
			if(retSD != FR_OK)
			{
				while(1)
				{
					printf("文件系统挂载失败\n");
					printf("停止执行");
				}
			}
			break;
		}
		case FR_OK:
		{
			printf("文件系统挂载成功！\n");
			break;
		}
		default:
			while(1)
			{
				printf("文件系统挂载出现未知错误\n");
			}
	}
	uint len;
	f_open(&SDFile,"README.txt",FA_OPEN_ALWAYS|FA_WRITE);
	char test[] = "---------------使用说明---------------\n\
pl文件夹下存储渐变色需要的文件，命名为pl1.bmp 到pl4.bmp，长度为LED灯个数，宽度为1\n\
如果没有pl目录或对应文件将导致文件读取错误\
根目录下存储显示的图形文件，命名为test.bmp,长度为LED灯个数,宽度不限";
	f_write(&SDFile,test,sizeof(test),&len);
	f_close(&SDFile);
}

void fileDecoder(char *fileName)
{
	printf("decoding\n");
	retSD = f_open(&SDFile,fileName,FA_READ	);
	if(retSD != FR_OK)
	{
		while(1)
		{
			printf("Fail to open File %s \n",fileName);
			//文件打开失败，串口报错，指示灯闪烁。
			HAL_Delay(100);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_14);
		}
	}
	
//解码png
	ShowBMP(&SDFile);
//关闭文件流
	f_close(&SDFile);

	printf("File open and decode success!\n");
}

void patternDecoder(char *fileName)
{
	static char* fileopened = NULL;
	if(fileopened != fileName)
		{
	retSD = f_open(&SDFile,fileName,FA_READ	);
	if(retSD != FR_OK)
	{
		while(1)
		{
			printf("Fail to open File %s \n",fileName);
			//文件打开失败，串口报错，指示灯闪烁。
			HAL_Delay(100);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_14);
		}
		}
	//读取png文件
		
	//解码png
		ShowPL(&SDFile);
	//关闭文件流
		f_close(&SDFile);
		fileopened = fileName;
	}
		else
	{
		RGB_Reflash();
	}
}
