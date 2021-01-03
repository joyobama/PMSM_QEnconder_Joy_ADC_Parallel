//############################################################
// FILE:  KEY.c
// Created on: 2016年4月8日
// Author: XY
// summary:KEY
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//版权所有，盗版必究
//DSP/STM32电机控制开发板
//硕历电子
//网址: https://shuolidianzi.taobao.com
//修改日期:2016/5/23
//版本：V16.3-1
//Author-QQ: 616264123
//电机控制QQ群：314306105
//############################################################

#include "KEY.h"
#include "GPIO_int.h"
#include "LCD12864.h"
#include "SCI_RS232.h"
extern   KEY    KEYPare;
extern  Test    TestPare;

unsigned char aim=0;
unsigned char MenuMN=0;
unsigned char MenuXY=0;
unsigned char MenuMNold=0x80;
//显示的全局变量-------------------------------//
unsigned char ShowTop=0;
unsigned char ShowTWoL0=0,ShowTWoL1=0,ShowTWoL2=0,ShowTWoL3=0,ShowTWoL6=0;

unsigned char ShowTHrL0_0=0,ShowTHrL0_1=0,ShowTHrL0_2=0,ShowTHrL0_3=0;
unsigned char ShowTHrL1_0=0,ShowTHrL1_1=0,ShowTHrL1_2=0,ShowTHrL1_3=0;
unsigned char ShowTHrL2_0=0,ShowTHrL2_1=0,ShowTHrL2_2=0,ShowTHrL2_3=0;
unsigned char  NumR=0,MainPOld=0,ShowTWoL1Old=0,ShowTWoL2Old=0;
unsigned char pBuf[17];
//----------------------------------------------//




void Key_Can(void)
{//*******************************************
	KEYPare.Key_num[0]=GpioDataRegs.GPCDAT.bit.GPIO81;
    if(KEYPare.Key_num[0]==0)		 //k1
	{    KEYPare.Key_count[0] ++;
		if(( KEYPare.Key_count[0] >=2)&&( KEYPare.Key_count[0] <30))
		{
			KEYPare.Key_switch[0]=1;   // KEYPare.Key_switch[0]
		}
		else
		if(( KEYPare.Key_count[0] ==30)||( KEYPare.Key_count[0] ==60))
		{
			KEYPare.KeyDataK|=0x0100;
			if( KEYPare.Key_count[0] ==60)  KEYPare.Key_count[0] =40;
		}
		else
		{	KEYPare.Key_switch[0]=0;
		}
	}
    else
    {  if( KEYPare.Key_count[0] !=0)
	   {	KEYPare.Key_count[0] =0;
		    if(KEYPare.Key_switch[0]==1)
		   {	KEYPare.KeyDataK|=0x01;
			    KEYPare.Key_switch[0]=0;
		   }
	   }
    }

//*******************************************
	KEYPare.Key_num[1]=GpioDataRegs.GPBDAT.bit.GPIO45;
	if(KEYPare.Key_num[1]==0)		 //k2
	{    KEYPare.Key_count[1] ++;
		if(( KEYPare.Key_count[1] >=2)&&( KEYPare.Key_count[1] <30))
		{
			KEYPare.Key_switch[1]=1;
		}
		else
		if(( KEYPare.Key_count[1] ==30)||( KEYPare.Key_count[1] ==60))
		{
			KEYPare.KeyDataK|=0x0200;
			if( KEYPare.Key_count[1] ==60)  KEYPare.Key_count[1] =40;
		}
		else
		{	KEYPare.Key_switch[1]=0;
		}
	}
	else
	{  if( KEYPare.Key_count[1] !=0)
	   {	 KEYPare.Key_count[1] =0;
			if(KEYPare.Key_switch[1]==1)
		   {	KEYPare.KeyDataK|=0x02;
				KEYPare.Key_switch[1]=0;
		   }
	   }
	}

//*******************************************
	KEYPare.Key_num[2]=GpioDataRegs.GPCDAT.bit.GPIO80;
	if(KEYPare.Key_num[2]==0)		 //k3
	{    KEYPare.Key_count[2] ++;
		if(( KEYPare.Key_count[2] >=2)&&( KEYPare.Key_count[2] <30))
		{	KEYPare.Key_switch[2]=1;
		}
		else
		if(( KEYPare.Key_count[2] ==30)||( KEYPare.Key_count[2] ==60))
		{
			KEYPare.KeyDataK|=0x0400;
			if( KEYPare.Key_count[2] ==60)  KEYPare.Key_count[2] =40;
		}
		else
		{	KEYPare.Key_switch[2]=0;
		}
	}
	else
	{  if( KEYPare.Key_count[2] !=0)
	   {	 KEYPare.Key_count[2] =0;
			if(KEYPare.Key_switch[2]==1)
		   {	KEYPare.KeyDataK|=0x04;
		        //LED2_REV;
				KEYPare.Key_switch[2]=0;
		   }
	   }
	}

//*******************************************
	KEYPare.Key_num[3]=GpioDataRegs.GPBDAT.bit.GPIO46;
	if(KEYPare.Key_num[3]==0)		 //k4
	{    KEYPare.Key_count[3] ++;
		if(( KEYPare.Key_count[3] >=2)&&( KEYPare.Key_count[3] <30))
		{	KEYPare.Key_switch[3]=1;
		}
		else
		if(( KEYPare.Key_count[3] ==30)||( KEYPare.Key_count[3] ==60))
		{
			KEYPare.KeyDataK|=0x0800;
			if( KEYPare.Key_count[3] ==60)  KEYPare.Key_count[3] =40;
		}
		else
		{	KEYPare.Key_switch[3]=0;
		}
	}
	else
	{  if( KEYPare.Key_count[3] !=0)
	   {	 KEYPare.Key_count[3] =0;
			if(KEYPare.Key_switch[3]==1)
		   {	KEYPare.KeyDataK|=0x08;
				KEYPare.Key_switch[3]=0;
		   }
	   }
	}
//*******************************************
	KEYPare.Key_num[4]=GpioDataRegs.GPBDAT.bit.GPIO47;
	if(KEYPare.Key_num[4]==0)		 //k5
	{    KEYPare.Key_count[4] ++;
		if(( KEYPare.Key_count[4] >=2)&&( KEYPare.Key_count[4] <30))
		{
		    KEYPare.Key_switch[4]=1;
		}
		else if(( KEYPare.Key_count[4] ==30)||( KEYPare.Key_count[4] ==60))
		{
			KEYPare.KeyDataK|=0x1000;
			if( KEYPare.Key_count[4] ==60)  KEYPare.Key_count[4] =40;
		}
		else
		{	KEYPare.Key_switch[4]=0;
		}
	}
	else
	{  if( KEYPare.Key_count[4] !=0)
	   {	 KEYPare.Key_count[4] =0;
			if(KEYPare.Key_switch[4]==1)
		   {	KEYPare.KeyDataK|=0x10;
				KEYPare.Key_switch[4]=0;
		   }
	   }
	}
}

//*****************按键处理****************************************************//
void Key_Dispose(void)
{ 	unsigned int iad=0;
    iad=KEYPare.KeyDataK;
    KEYPare.KeyDataK=0;
	if ((iad & 0x1f1f)!=0)
	{	switch(iad&0x1f1f)
		{	case 0x0001: //上
				if((MenuMN==0)&&(ShowTWoL0==0))
				{	if((MenuXY&0x03)==0)
					{	MenuXY=0;
					}
					else  MenuXY--;
				}
				LED2_REV;
				break;
			case 0x0002: //下
				if((MenuMN==0)&&(ShowTWoL0==0))
				{
					if((MenuXY&0x03)>=2)
					{	MenuXY=0;
					}
					else {MenuXY++;
					}

				}
				LED2_REV;
				break;
			case 0x0004:  //左
				if(MenuMN==0)
				{	if(ShowTWoL0==0)
					{	ShowTWoL0=0;
					}
					else ShowTWoL0--;
				}
				LED2_REV;
				break;
			case 0x0008: //右
				if(MenuMN==0)
				{	if(ShowTWoL0<2)
					{	ShowTWoL0++;
					}
					else ShowTWoL0=0;
				}
				LED2_REV;
				break;
			case 0x0010: // 确定
				if(MenuMN==0)
				{	if(ShowTWoL0==0)
					{   MenuMN |=0x80;
						ShowTop=1;
						ShowTWoL0=0;
						Show_Clr_All();
						Lcd_Clera();
						switch(MenuXY & 0x03)
						{	case 0:
								ShowTWoL1=0;
								break;
							case 1:
								ShowTWoL1=1;
								break;
							case 2:
								ShowTWoL1=2;
							default:
								break;
						}
					}
				}
				else if(MenuMN & 0x80)
				{	MenuMN=0;
					ShowTop=0;
					ShowTWoL1=0;
					Show_Clr_All();
					Lcd_Clera();
				}
				LED2_REV;
				break;
			case 0x0100:  //
				LED2_REV;
				break;
			case 0x0200:  //
				LED2_REV;
				break;
			case 0x0400:  //
				LED2_REV;
				break;
			case 0x0800:  //
				LED2_REV;
				break;
			case 0x1000:  //
				LED2_REV;
				break;
			default:;
		 	break;

		}
	}
}




//TestPare
void Show_disp(void)
{	switch(ShowTop)
	{	case 0:     //
			if((ShowTWoL0!=MainPOld)||(MenuXY!=ShowTWoL2Old))
			{	//Show_Clr_All();
				Lcd_Clera();
			}
			switch(ShowTWoL0)    //主界面
			{	case 0:
					StrCopyBTA(pBuf,(unsigned char *)"永磁同步正交编码",16);
					pBuf[16]='\0';
					Lcd_ShowStr(0,48,pBuf);

					Lcd_ShowStr(0,32,(unsigned char *)"  用户参数       \0");
					Lcd_ShowStr(0,16,(unsigned char *)"  设备状态      \0");
					Lcd_ShowStr(0,0,(unsigned char *)"  用户定义    \0");
					Lcd_ShowStr(0,32-((MenuXY & 0x03)<<4),(unsigned char *)"=>\0");
					ShowTWoL2Old=MenuXY;
					break;
				case 1:
					StrCopyBTA(pBuf,(unsigned char *)" d轴电流:",9);
					sFormatLong(TestPare.id_test,0x04,pBuf+9);
					pBuf[13]=' ';
					pBuf[14]='\0';
					Lcd_ShowStr(0,48,pBuf);

					StrCopyBTA(pBuf,(unsigned char *)" q轴电流:",9);
					sFormatLong(TestPare.iq_test,0x04,pBuf+9);

                    pBuf[13]=' ';
                    pBuf[14]='\0';
                    Lcd_ShowStr(0,32,pBuf);

                    StrCopyBTA(pBuf,(unsigned char *)" d轴电压:",9);
                    sFormatLong(TestPare.ud_test,0x04,pBuf+9);
                    pBuf[13]=' ';
                    pBuf[14]='\0';
                    Lcd_ShowStr(0,16,pBuf);

                    StrCopyBTA(pBuf,(unsigned char *)" q轴电压:",9);
                    sFormatLong(TestPare.uq_test,0x04,pBuf+9);
                    pBuf[13]=' ';
                    pBuf[14]='\0';
                    Lcd_ShowStr(0,0,pBuf);
					break;
				case 2:
					StrCopyBTA(pBuf,(unsigned char *)"  用户定义2    ",15);
					pBuf[15]='\0';
					Lcd_ShowStr(0,48,pBuf);

				break;

			default:
				break;
			}
		MainPOld=ShowTWoL0;
		break;
	case 1:      //菜单界面
		if(ShowTWoL1!=ShowTWoL1Old)
		{	//Show_Clr_All();
			Lcd_Clera();
		}
		switch(ShowTWoL1)
		{	case 0:
				StrCopyBTA(pBuf,(unsigned char *)"母线电压:",9);
				sFormatLong(TestPare.fact_BUS_Voil,0x12,pBuf+9);
				//sFormatLong(243,0x12,pBuf+9);
				pBuf[13]=' ';
                pBuf[14]='V';
                pBuf[15]='\0';
                Lcd_ShowStr(0,48,pBuf);

                StrCopyBTA(pBuf,(unsigned char *)"母线电流:",9);
                sFormatLong(TestPare.fact_BUS_Curr,0x21,pBuf+9);
                pBuf[13]=' ';
                pBuf[14]='A';
                pBuf[15]='\0';
                Lcd_ShowStr(0,32,pBuf);

				StrCopyBTA(pBuf,(unsigned char *)"当前转速:",9);
				sFormatLong(TestPare.Speed_fact,0x04,pBuf+9);
                pBuf[13]='R';
                pBuf[14]='P';
                pBuf[15]='M';
                pBuf[16]='\0';
                Lcd_ShowStr(0,16,pBuf);

				StrCopyBTA(pBuf,(unsigned char *)"设定转速:",9);
				sFormatLong(TestPare.Speed_target,0x04,pBuf+9);
				pBuf[13]='R';
                pBuf[14]='P';
                pBuf[15]='M';
                pBuf[16]='\0';
                Lcd_ShowStr(0,0,pBuf);
				break;
			case 1:
				Lcd_ShowStr(0,48,(unsigned char *)"起停方式：      \0");
				Lcd_ShowStr(0,32,(unsigned char *)"    模拟量控制 \0");
				break;
			case 2:
				Lcd_ShowStr(0,48,(unsigned char *)"  用户定义1 \0");

				break;
			default:
				break;
			}
		ShowTWoL1Old=ShowTWoL1;
		break;
	case 2:
		break;
	default:;
		break;
	}
}

//===========================================================================
// No more.
//===========================================================================
