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
					printf("�ļ�ϵͳ����ʧ��\n");
					printf("ִֹͣ��");
				}
			}
			break;
		}
		case FR_OK:
		{
			printf("�ļ�ϵͳ���سɹ���\n");
			break;
		}
		default:
			while(1)
			{
				printf("�ļ�ϵͳ���س���δ֪����\n");
			}
	}
	uint len;
	f_open(&SDFile,"README.txt",FA_OPEN_ALWAYS|FA_WRITE);
	char test[] = "---------------ʹ��˵��---------------\n\
pl�ļ����´洢����ɫ��Ҫ���ļ�������Ϊpl1.bmp ��pl4.bmp������ΪLED�Ƹ��������Ϊ1\n\
���û��plĿ¼���Ӧ�ļ��������ļ���ȡ����\
��Ŀ¼�´洢��ʾ��ͼ���ļ�������Ϊtest.bmp,����ΪLED�Ƹ���,��Ȳ���";
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
			//�ļ���ʧ�ܣ����ڱ���ָʾ����˸��
			HAL_Delay(100);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_14);
		}
	}
	
//����png
	ShowBMP(&SDFile);
//�ر��ļ���
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
			//�ļ���ʧ�ܣ����ڱ���ָʾ����˸��
			HAL_Delay(100);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_13);
			HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_14);
		}
		}
	//��ȡpng�ļ�
		
	//����png
		ShowPL(&SDFile);
	//�ر��ļ���
		f_close(&SDFile);
		fileopened = fileName;
	}
		else
	{
		RGB_Reflash();
	}
}
