#include "menu.h"
/*
saber menu:

|saber|printer|settings|
------------------------
	run1,							|■| 滑
	run2,							|■| 条
	run3,							|■|
	pl1,							|■|
	pl2,							|  |
	pl3,							|  |
	pl4,							|  |
	pl5,							|  |
	RED,							|  |
	GREEN,						|  |
	BLUE,							|  |
	YELLOW,						|  |
	MAGENTA,					|  |
	BLACK,						|  |
	WHITE							|  |

printer menu:

|saber|printer|settings|
------------------------
	name1							|■| 滑
	name2							|■| 条
	name3							|■|
	name4							|■|
	name5							|  |
	name6							|  |
	....

settings menu:

|saber|printer|settings|
------------------------
	brightness+				|■| 滑
	brightness-				|■| 条
	speed+						|■|
	speed-						|■|
	     							|  |
										|  |
*/

/**
	按键引脚定义：
	上 - E pin10
	下 - E pin11
	左 - E pin12
	右 - E pin13
	中 - E pin14
	*/

/* 工作状态 */
WorkModeType WorkMode = saber;
/* 光剑模式选择 */
saberType WorkSaberType = run1;
/* 消抖 */
static int32_t time_counter = 0;
static uint8_t line = 0;
brightness_State brightness = L1;
uint8_t printerFlag = 0;

static const char string1[] = "brightness +";
static const char string2[] = "brightness -";

menu menuChoose = _Saber;

char saberName[80];
char imageName[80];

const uint8_t l1[] = "|saber";
const uint8_t l2[] = "|print";
const uint8_t l3[] = "|Setting|";

static void menu_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2,uint8_t color)
{
	int16_t t; 
	int16_t xerr=0,yerr=0,delta_x,delta_y,distance; 
	int16_t incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{ 
		OLED_Set_Pixel(uRow,uCol,color);
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
	OLED_Display();
} 

static void menu_Fill(uint8_t sx,uint8_t sy,uint8_t ex,uint8_t ey,uint8_t color)
{  	
	uint8_t i,j;			
	uint8_t width=ex-sx+1; 		//得到填充的宽度
	uint8_t height=ey-sy+1;		//高度
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
				OLED_Set_Pixel(sx+j, sy+i,color);
		}		
	}
}

static void menu_ShowDragBar(void)
{
	static uint8_t position = min_start;
	static menu lastmenu = _Saber;
	uint8_t mystring[16];
	//切换菜单时初始化选项
	if(menuChoose != lastmenu)
	{
		lastmenu = menuChoose;
		position = min_start;
		line = 0;
	}
	
	switch(menuChoose)
	{
		case _Saber:
		{
			position = 56 / numOfsaberType * line + min_start;
			if(line+5 > numOfsaberType)
			{
				for(uint8_t i = line;i<=numOfsaberType;i++)
				{
					sprintf((char*)mystring,"%s",saberNamelist[i]);
					if(i == WorkSaberType)
					{
						GUI_ShowString(8,(i-line)*8+8,mystring,8,0);
					}
					else
					{
						GUI_ShowString(8,(i-line)*8+8,mystring,8,1);
					}	
				}
			}
			else
			{
				for(uint8_t i = line;i<=line+5;i++)
				{
					sprintf((char*)mystring,"%s",saberNamelist[i]);
					if(i == WorkSaberType)
					{
						GUI_ShowString(8,(i-line)*8+8,mystring,8,0);
					}
					else
					{
						GUI_ShowString(8,(i-line)*8+8,mystring,8,1);
					}	
				}
			}
			break;
		}
		case _Printer:
		{
			position = min_start;
			for(uint8_t i = 0;i<5;i++)
			{
				sprintf((char*)mystring,"image%d",i);
				if(i == line)
				{
					GUI_ShowString(8,i*8+8,mystring,8,0);
				}
				else
				{
					GUI_ShowString(8,i*8+8,mystring,8,1);
				}	
			}
			break;
		}
		case _Setting:
		{
			position = min_start;
			sprintf((char*)mystring,"brightness = %d",maxBrightness-brightness);
			GUI_ShowString(8,9,mystring,8,1);
			GUI_ShowString(8,18,(uint8_t *)string1,8,line & 1);
			GUI_ShowString(8,27,(uint8_t *)string2,8,!(line & 1));
			break;
		}
		default:
			printf("Error!\n");
	}
	/* 绘制位置滑块 */
	menu_DrawLine(115,8,115,64,1);
	menu_DrawLine(125,8,125,64,1);
	menu_Fill(115,position,125,position+10,1);
}

void ModeMenu(void)
{
	uint8_t *ptr = (uint8_t*)l1;
	OLED_Fill(0);
	switch(menuChoose)
	{
		case _Saber:
		{
			GUI_ShowString(0,0,ptr,8,0);
			ptr = (uint8_t*)l2;
			GUI_ShowString(35,0,ptr,8,1);
			ptr = (uint8_t*)l3;
			GUI_ShowString(75,0,ptr,8,1);
			break;
		}
		case _Printer:
		{
			GUI_ShowString(0,0,ptr,8,1);
			ptr = (uint8_t*)l2;
			GUI_ShowString(35,0,ptr,8,0);
			ptr = (uint8_t*)l3;
			GUI_ShowString(75,0,ptr,8,1);
			break;
		}
		case _Setting:
		{
			GUI_ShowString(0,0,ptr,8,1);
			ptr = (uint8_t*)l2;
			GUI_ShowString(35,0,ptr,8,1);
			ptr = (uint8_t*)l3;
			GUI_ShowString(75,0,ptr,8,0);
			break;
		}
	}

	menu_ShowDragBar();
}


/** @brief 中断处理函数
  *
  * 
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
/*
	上 - pin10
	下 - pin11
	左 - pin12
	右 - pin13
	中 - pin14
*/
	static int32_t lastTriggerTime = 0;
	if(lastTriggerTime - time_counter < 200 && lastTriggerTime - time_counter > -200 )
	{
		return;
	}
	else
	{
		lastTriggerTime = time_counter;
	}
	switch(GPIO_Pin)
	{
		case GPIO_PIN_10:
		{
			if(line != 0) line--;
			break;
		}
		case GPIO_PIN_11:
		{
			switch(menuChoose)
			{
				case _Saber:
				{
					if(line < numOfsaberType)line++;
					break;
				}
				case _Printer:
				{
					if(line < numOfimage)line++;
					break;
				}
				case _Setting:
				{
					if(line < 4)line++;
					break;
				}
			}
			break;
		}
		case GPIO_PIN_12: //菜单选择 <-
		{
			if(menuChoose != _Saber) menuChoose--;
			break;
		}
		case GPIO_PIN_13: //菜单选择 ->
		{
			if(menuChoose != _Setting) menuChoose++;
			break;
		}
		case GPIO_PIN_14: //confirm
		{
			switch(menuChoose)
			{
				case _Saber:
				{
					WorkMode = saber;
					WorkSaberType = (saberType)line;
					break;
				}
				case _Printer:
				{
					/* load file name */
					WorkMode = printer;
					sprintf(imageName,"0:/image/image%d.bmp",line);
					/* set print flag*/
					printerFlag = 1;
					break;
				}
				case _Setting:
				{
					if(line == 0 && brightness > 0)brightness--;
					if(line == 1 && brightness <= maxBrightness-1) brightness++;
					break;
				}
			}
			break;
		}
		default:
		{
			printf("keyControl: warning! undefined step\n");
			break;
		}
	}
	/* 每次改变设置都需要刷新菜单 */
	refleshFlag = 1;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	time_counter++;
}
