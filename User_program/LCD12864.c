//############################################################
// FILE:  LCD12864.c
// Created on: 2016年4月11日
// Author: XY
// summary:LCD12864
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

#include "LCD12864.h"
#include "GPIO_int.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

unsigned char Str_Length=0,y1old=0;

//**********************************************************//
//滑条
//**********************************************************//
const unsigned char DrawR[]={
0xFF,0x99,0xBD,0xFF,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,
0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0x81,0xFF,0xBD,0x99,0xFF
};



unsigned char LCD_DATAZHUHUAN(unsigned char DData)
{unsigned char ui=0;
	ui=(DData&0x01)<<7;
	ui|=(DData&0x02)<<5;
	ui|=(DData&0x04)<<3;
	ui|=(DData&0x08)<<1;
	ui|=(DData&0x10)>>1;
	ui|=(DData&0x20)>>3;
	ui|=(DData&0x40)>>5;
	ui|=(DData&0x80)>>7;
	return(ui);
}

unsigned char LCD_Read(void)
{   unsigned char Data=0;
	EALLOW;
	/***************LCD_D0*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO79 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO79=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO79=1;
	/***************LCD_D1*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO78 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO78=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO78=1;
	/***************LCD_D2*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO77 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO77=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO77=1;
	/***************LCD_D3*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO76 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO76=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO76=1;
	/***************LCD_D4*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO75 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO75=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO75=1;
	/***************LCD_D5*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO74 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO74=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO74=1;
	/***************LCD_D6*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO73 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO73=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO73=1;
	/***************LCD_D7*********************/
	GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0;  									// GPIO11 = GPIO
	GpioCtrlRegs.GPCDIR.bit.GPIO72 = 0;
	GpioCtrlRegs.GPCPUD.bit.GPIO72=0;
	GpioDataRegs.GPCCLEAR.bit.GPIO72=1;
	EDIS;
	DELAY_US(50);
	Data=GpioDataRegs.GPCDAT.bit.GPIO72<<7;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO73<<6;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO74<<5;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO75<<4;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO76<<3;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO77<<2;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO78<<1;
	DELAY_US(50);
	Data|=GpioDataRegs.GPCDAT.bit.GPIO79;
	DELAY_US(50);
	return(Data);
}

//*****************************************************//
//向LCD写说指令或写数据******传送数据/指令
//当DI=0,传送指令,当DI=1,传送数据
//*****************************************************//
void TransferData(unsigned char Data,unsigned char DI)
{
	    unsigned long Bi,Di;
	  	LCD_RW=0;         //写
	  	DELAY_US(100);
	  	if(DI==0) LCD_RS=0;  //指令
	  	else if(DI==1) LCD_RS=1; //数据
	  	DELAY_US(100);
	  	LCD_EN=1;         //允许
	  	DELAY_US(100);
	  	LCD_DATA&=~0X0000FF00;
	  	Bi=LCD_DATAZHUHUAN(Data);
	    Di=Bi<<8;
	    LCD_DATA|=Di;
	  	DELAY_US(100);
	  	LCD_EN=0;
	  	DELAY_US(100);
	  	LCD_RW=1;

}
//-----------------------------------------------------//
//读取LCD上的数据
//----------------------------------------------------//
unsigned char Lcd_Read(void)
{
	unsigned char Data;
	LCD_RS=0;         //指令
	LCD_RW=1;         //读
	LCD_EN=1;         //允许
	Data=0xff;
	DELAY_US(100);
	Data=LCD_Read();
	DELAY_US(100);
	LCD_EN=0;         //禁止
	Init_LCD12864_Gpio();
	return (Data);
}
//-----------------------------------------------------//
//读取LCD上的忙位
//----------------------------------------------------//
void Buy_Read(void)
{	unsigned char Data;
	LCD_RS=0;         //指令
	LCD_RW=1;         //读
	LCD_EN=1;         //允许
	Data=0xff;
	DELAY_US(100);
	Data=LCD_Read();
	DELAY_US(100);
	while((Data & 0x80)==0x80);
	LCD_EN=0;         //禁止
	Init_LCD12864_Gpio();
}


//****************************************************************************//
//全屏清除 清除GDRAM
//****************************************************************************//
void  Show_Clr_All(void)
{	unsigned int i,j;
	TransferData(0x34,0);     //扩展指令命令
	TransferData(0x36,0);     //扩展指令命令
	for(i=0;i<64;i++)
	{	j=8*(i/32);
		TransferData(0x80+(i&0x1f),0);      //设定行地址(y坐标)
		TransferData(0x80+j,0);      //设定行地址(y坐标)
		for(j=0;j<8;j++)
		{
		TransferData(0x00 ,1);
		TransferData(0x00 ,1);
		}

	}
	TransferData(0x30,0);          //恢复到基本指令集   */
}
//****************************************************************************//
//****************************************************************************//

//*****************************************************//
//LCD清屏函数
//*****************************************************//
void  Lcd_Clera(void)
{
	unsigned char i;
	TransferData(0x80,0);
	for(i=0;i<64;i++)
	{	TransferData(0x20,1);
	}
}
//*****************************************************//
//LCD汉字库初始化
//*****************************************************//
void LCD12864_init(void)   //   LCD12864_init  Lcd_Init
{   LCD_REST=0;
	DELAY_US(50);//延迟100ms
	LCD_REST=1;
	DELAY_US(50);
	TransferData(0x30,0);  //功能设定:RE=0:不扩充指令集,G=0 :关闭图形显示
	DELAY_US(20);
	TransferData(0x30,0);  //判断是否设置成功
	DELAY_US(20);
	TransferData(0x08,0);  //整体显示
	DELAY_US(20);
	TransferData(0x10,0);  //光标设置
	DELAY_US(20);
	TransferData(0x0C,0);  //显示开
	DELAY_US(20);
	TransferData(0x01,0);  //清屏
	DELAY_US(20);
	TransferData(0x06,0);  //光标设置,光标从右向左加1位移动
	DELAY_US(20);
}


//*****************************************************//
//LCD显示汉字
//*****************************************************//
void Lcd_ShowStr1(unsigned char x,unsigned char y,unsigned char *adder)	 //用于显示字符
{	unsigned char i=0;
	if(x>16) {x=16;}
	else if(0<x<16) { }
	else if(x<=0) {x=0; }
	if(y>48) {y=48;}
	else if(0<y<48) { }
	else if(y<=0) {y=0;}
	if(y==48)  TransferData(0x80+x,0);  //设置DDRAM起始地址
	else if(y==32)  TransferData(0x90+x,0);  //设置DDRAM起始地址
	else if(y==16)  TransferData(0x88+x,0);  //设置DDRAM起始地址
	else if(y==0)  TransferData(0x98+x,0);  //设置DDRAM起始地址
	for(i=x;i<=15-x;i++)   //while(adder[j]!='\0')   //
	{
		TransferData(*adder,1);   //传送数据
	   	adder++;

	}
}

void Lcd_ShowStr(unsigned char x,unsigned char y,unsigned char *adder)
{	unsigned char i,j=0;
	switch(y)
	{	case 48:  i=0x80+x;
			break;
		case 32: i=0x90+x;
			break;
		case 16: i=0x88+x;
			break;
		case 0: i=0x98+x;
			break;
		default:
			break;
	}
	TransferData(i,0);
	while(adder[j]!='\0')
	{	TransferData(adder[j],1);   //传送数据
		j++;
	}
}
//****************************************************************************//
//****************************************************************************//


//****************************************************************************//
//LCD打点   x为横轴坐标 y为纵轴坐标
//color=1为该点填充1    color=0 为该点填充0
//*****************************************************//
void Show_Point(unsigned char x,unsigned char y,unsigned char color)
{	unsigned char x_Dyte,x_Bit;    //定义列地址的字节，及在字节中的哪1位
	unsigned char y_Dyte,y_Bit;    //定义行为上下两个屏(取值为0，1)，行地址(取值为0~31)
	unsigned char GDRAM_Hbit,GDRAM_Lbit;
	TransferData(0x36,0);     //扩展指令命令
	x_Dyte=x/16;        //计算在16个字节中的哪一个
	x_Bit=x&0x0f;        //计算在该字节中的哪一位
	y_Dyte=y/32;        //0为上半屏，1为下半屏
	y_Bit=y&0x1f;        //计算在0~31当中的哪一行
	TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
	Lcd_Read();         //预读取数据
	GDRAM_Hbit=Lcd_Read();      //读取当前显示高8位数据
	GDRAM_Lbit=Lcd_Read();      //读取当前显示低8位数据
	DELAY_US(1);
	TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
	if(x_Bit<8)          //判断其在高8位，还是在低8位
	{
  		if(color==1)
  		{
   			TransferData(GDRAM_Hbit | (0x01<<(7-x_Bit)),1); //置位GDRAM区高8位数据中相应的点
  		}
  		else
   			TransferData(GDRAM_Hbit & (~(0x01<<(7-x_Bit))),1); //清除GDRAM区高8位数据中相应的点

  			TransferData(GDRAM_Lbit,1);       //显示GDRAM区低8位数据
	}
	else
	{	TransferData(GDRAM_Hbit,1);
  		if(color==1)
   			TransferData(GDRAM_Lbit|(0x01<<(15-x_Bit)),1); //置位GDRAM区高8位数据中相应的点
  		else
   			TransferData(GDRAM_Lbit & (~(0x01<<(15-x_Bit))),1);//清除GDRAM区高8位数据中相应的点

	}
	TransferData(0x30,0);          //恢复到基本指令集
}
//****************************************************************************//
//****************************************************************************//


//*******************************************************//
//LCD显示图片刷屏(画满屏)
//*******************************************************//
void Show_Picture(unsigned char  *adder)
//void Show_Picture(void)
{   unsigned char i,j;
////******显示上半屏幕********************//
 	TransferData(0x36,0);  //Extended Function Set RE=1: extended instruction
    //delay_us(10);
    for(i=0;i<32;i++)              //
    {
      TransferData((0x80 + i),0); //SET  垂直地址 VERTICAL ADD
      TransferData(0x80,0);       //SET  水平地址 HORIZONTAL ADD
      for(j=0;j<16;j++)
       {
         TransferData(*adder,1);
		 //TransferData(0XFF,1);
         adder++;
       }
    }
//********显示下半屏幕*****************//
   for(i=0;i<32;i++)              //
    {
      TransferData((0x80 + i),0); //SET 垂直地址 VERTICAL ADD
      TransferData(0x88,0);       //SET 水平地址 HORIZONTAL ADD
      for(j=0;j<16;j++)
       {	//TransferData(0XFF,1);
         TransferData(*adder,1);
         adder++;
       }
    }
	TransferData(0x30,0);  //Extended Function Set RE=1: extended instruction
}
//****************************************************************************//
//****************************************************************************//


//****************************************************************************//
//LCD写一个字节   x为横轴坐标 y为纵轴坐标
//Data 为8位数据
//ATunm属性   1位读取当前八位数据在或要写的数据
//*****************************************************//
void Show_Byte(unsigned char x,unsigned char y,unsigned char Data,unsigned char ATunm)
{	unsigned char x_Dyte,x_Bit;    //定义列地址的字节，及在字节中的哪1位
	unsigned char y_Dyte,y_Bit;    //定义行为上下两个屏(取值为0，1)，行地址(取值为0~31)
	unsigned char GDRAM_Hbit,GDRAM_Lbit;
	TransferData(0x36,0);     //扩展指令命令
	x_Dyte=x/16;        //计算在16个字节中的哪一个
	x_Bit=x&0x0F;        //计算在该字节中的哪一位
	y_Dyte=y/32;        //0为上半屏，1为下半屏
	y_Bit=y&0x1f;        //计算在0~16当中的哪一行
	TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
	Lcd_Read();         //预读取数据
	GDRAM_Hbit=Lcd_Read();      //读取当前显示高8位数据
	GDRAM_Lbit=Lcd_Read();      //读取当前显示低8位数据
	//delay_us(1);
	TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
	TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
	if(x_Bit<8)          //判断其在高8位，还是在低
   	{
		if(ATunm & 0x01)
		{	TransferData(GDRAM_Hbit |Data ,1); //置位GDRAM区高8位数据中相应的点
		}
		else
		{	TransferData(Data ,1); //置位GDRAM区高8位数据中相应的点
		}
  		TransferData(GDRAM_Lbit,1);       //显示GDRAM区低8位数据
	}
	else
	{	TransferData(GDRAM_Hbit,1); //置位GDRAM区高8位数据中相应的点
		if(ATunm & 0x01)
		{	TransferData(GDRAM_Lbit | Data,1);     //显示GDRAM区低8位数据
		}
		else
		{	TransferData(Data ,1); //置位GDRAM区高8位数据中相应的点
		}
	 }
	TransferData(0x30,0);          //恢复到基本指令集
}
//****************************************************************************//
//****************************************************************************//


void  Show_Picture_Area(unsigned char x,unsigned char y,const unsigned char *Data,unsigned char W,unsigned char H)
{   unsigned char i,j;
	unsigned char x_Dyte,x_Bit;    //定义列地址的字节，及在字节中的哪1位
	unsigned char y_Dyte,y_Bit;    //定义行为上下两个屏(取值为0，1)，行地址(取值为0~31)
	volatile unsigned char GDRAM_Hbi=0,GDRAM_Lbi=0;
	if(x>127) return;
	if(y>63) return;
	W=(W+7)/8;
	TransferData(0x36,0);     //扩展指令命令
	for(i=0;i<H;i++)
	{	x_Dyte=x/16;        //计算在16个字节中的哪一个
		x_Bit=x&0x0F;        //计算在该字节中的哪一位
		y_Dyte=y/32;        //0为上半屏，1为下半屏
		y_Bit=y&0x1f;        //计算在0~16当中的哪一行
		TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
		Lcd_Read();         //预读取数据
		GDRAM_Hbi=Lcd_Read();      //读取当前显示高8位数据
		GDRAM_Lbi=Lcd_Read();      //读取当前显示低8位数据
		TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
		if(x_Bit<8)          //判断其在高8位，还是在低
   		{	for(j=0;j<W;j++)
			{	TransferData(*Data,1); //置位GDRAM区高8位数据中相应的点
				Data++;
			}
		}
		else
		{	TransferData(GDRAM_Hbi,1); //置位GDRAM区高8位数据中相应的点
			for(j=0;j<W;j++)
			{	TransferData(*Data ,1); //置位GDRAM区高8位数据中相应的点
				Data++;
			}
		 }
		 y++;
	}
	TransferData(0x30,0);          //恢复到基本指令集
}
//****************************************************************************//
//****************************************************************************//


//*****************滑条*****************************************************
//****************************************************************************
//参数说明： x y指定显示区域的起始点坐标
//           // dat	要输出显示的图形或汉字点阵数组。
//            y1 是滑块的纵坐标
//            H要滑块的高度
//         // ATunm属性//unsigned char W,unsigned char H,
//****************************************************************************//
void  Show_Draw_Run(unsigned char x,unsigned char y,unsigned char y1,unsigned char H)
{	unsigned char i,j,Data;

	if(y1==y1old)
	{	for(j=0;j<64;j++)
		{	Data=DrawR[j];
			Show_Byte(x,y,Data,0x01);
			y++;
		}
	}
	else
	{	for(j=0;j<64;j++)
		{	Data=DrawR[j];
			Show_Byte(x,y,Data,0x00);
			y++;
		}
	}
	y1old=y1;
	for(i=0;i<H;i++)//逐行写，行数要小于区域高度
	{   Show_Byte(x,y1,0xff,0x01);
		y1++;
	}
}
//****************************************************************************//
//****************************************************************************//


//****************************************************************************//
//区域清除 清除GDRAM
//          x、y指定清除区域的起始点坐标
//          dat	要输出显示的数据
//          W	区域的长度
//          H	区域的高度
//****************************************************************************//
void  Show_Clr_Area(unsigned char x,unsigned char y,unsigned char Data,unsigned char W,unsigned char H)
{	unsigned char i,j;
	unsigned char x_Dyte,x_Bit;    //定义列地址的字节，及在字节中的哪1位
	unsigned char y_Dyte,y_Bit;    //定义行为上下两个屏(取值为0，1)，行地址(取值为0~31)
	volatile unsigned char GDRAM_Hb=0,GDRAM_Lb=0;
	TransferData(0x36,0);     //扩展指令命令
	if(x>127) return;
	if(y>63) return;
	W=(W+7)/8;
	for(i=0;i<H;i++)
	{
		x_Dyte=x/16;        //计算在16个字节中的哪一个
		x_Bit=x&0x0F;        //计算在该字节中的哪一位
		y_Dyte=y/32;        //0为上半屏，1为下半屏
		y_Bit=y&0x1f;        //计算在0~16当中的哪一行
		TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
		Lcd_Read();         //预读取数据
		GDRAM_Hb=Lcd_Read();      //读取当前显示高8位数据
		GDRAM_Lb=Lcd_Read();      //读取当前显示低8位数据

		TransferData(0x80+y_Bit,0);      //设定行地址(y坐标)
		TransferData(0x80+x_Dyte+8*y_Dyte,0);    //设定列地址(x坐标)，并通过8*y_Dyte选定上下屏
		if(x_Bit<8)          //判断其在高8位，还是在低
   		{	for(j=0;j<W;j++)
			{	TransferData(Data ,1); //置位GDRAM区8位数据中相应的点
			}
		}
		else
		{	TransferData(GDRAM_Hb,1);     //显示GDRAM区低8位数据
			for(j=0;j<W;j++)
			{	TransferData(Data ,1);
			}
		}
		y++;
	}
	TransferData(0x30,0);          //恢复到基本指令集   */
}
//****************************************************************************//
//****************************************************************************//




//****************************************************************************//
//****************************************************************************//
void StrCopyBTA( unsigned char *str1, unsigned char *str2, unsigned char a)
{ unsigned char b;
	for(b=0;b<a;b++)
	{	str1[b]=str2[b];
		if(str2[b]==0) return;
	}
}
/*********************************************
 函数功能： 格式化一个长整型到字符串
 入口参数： uStyle.3-uStyle.0: 输出数据位数(不包括小数点)
 			uStyle.7-uStyle.4: 显示小数点位数,全零不显示小数点
 			uStyle.15=0:左对齐方式, =1:右对齐方式
 出口参数：
 备    注:  关于数据位数:如果实际数据位数大于定义的数据位数,则按实际的返回
                如果实际的数据位数小于定义的数据位数,则不管左对齐还是右对齐,均补空格
**********************************************/

void utoa( char *DStr,int DATA,unsigned char N)
{   int ia=0,ib=0,ic=0,im=0;
    int id=0;
    if(DATA>=10000)     {im=5;ib=10000;}
    else if(DATA>=1000) {im=4;ib=1000;}
    else if(DATA>=100) {im=3;ib=100;}
    else if(DATA>=10)  {im=2;ib=10;}
    else if(DATA>=1)   {im=1;ib=1;}
    else  {im=0;ib=0;}

    if(im!=0)
    {   for(ia=0;ia<im;ia++)
        {   id=DATA/ib;
            DStr[ic++]=id+'0';
            DATA=DATA%ib;
            ib=ib/10;
        }
    }
    else
    {
        DStr[ic++]='0';
    }
    DStr[ic]='\0';
}

/*
unsigned char strlenle( char string[])
{	unsigned char i=0;
	while(string[i]!='\0') i++;
	return i;
}*/
void strcpyy( unsigned char *strDest, const  char *strSrc)
{  /* if ((strDest == NULL) || (strSrc == NULL))
	return NULL ;
	if(strDest==strSrc)
	return strDest ;
	unsigned char *tempptr = strDest ;
	while( (*strDest++ = *strSrc++) !='\0');
	return tempptr ;*/
	unsigned char i=0;
	while(strSrc[i]!='\0')
	{
		strDest[i]=(unsigned char)strSrc[i];
		i++;
	}
}

/*********************************************
 函数功能： 格式化一个长整型到字符串
 入口参数：   uStyle.3-uStyle.0: 输出数据位数(不包括小数点)
        uStyle.7-uStyle.4: 显示小数点位数,全零不显示小数点
        uStyle.15=0:左对齐方式, =1:右对齐方式
 出口参数：
 备    注:  关于数据位数:如果实际数据位数大于定义的数据位数,则按实际的返回
                如果实际的数据位数小于定义的数据位数,则不管左对齐还是右对齐,均补空格
**********************************************/
void sFormatLong(int lData, unsigned int uStyle,  unsigned char *pStr)
{   char pTemp[5];
	char i, j, k, iStrLen, iDataLen, iPointLen;
	pStr[0]=0;								// 将字符串置空
	utoa(pTemp,lData,5);// 长整型转换为字符串
	iStrLen=strlen(pTemp);
	iDataLen = uStyle&0x000f;
	iPointLen = (uStyle&0x00f0)>>4;
											// 如果数据长度或显示小数点位数超长则不处理
	if((iDataLen>9) || (iPointLen>8))  return;

	if(iPointLen==0)
	{
		if(uStyle & 0x8000)					// 无小数点右对齐
		{
			if(iDataLen > iStrLen)
			{								// 当定义位数大于实际位数时左边补空格
				for(i=0; i<(iDataLen-iStrLen); i++)	pStr[i]=0x20;
				strcpyy(pStr+iDataLen-iStrLen, pTemp);

			}
			else
			{  ;  }
			   strcpyy(pStr, pTemp);		// 当定义位数小于实际位数时直接拷贝字符串
		}
		else
		{									// 无小数点左对齐
		    strcpyy(pStr, pTemp);			// 先拷贝字符串
			if(iDataLen > iStrLen)			// 当定义位数大于实际位数时右边补空格
			{
				for(i=iStrLen; i<iDataLen; i++) pStr[i]=0x20;
				pStr[i]=0;
			}
		}
	}
	else
	{
		if((uStyle & 0x8000)==0)				// 左对齐, 显示小数点
		{
			if(iPointLen >= iStrLen)
			{									// 如果小数位数大于或等于实际数长,先放置"0."
				pStr[0]='0'; pStr[1]='.';		// 放置小数点后的"0"
				for(i=2; i<(2+iPointLen-iStrLen); i++) pStr[i]='0';
				strcpyy(pStr+i, pTemp);			// 放置实际数字
				i += iStrLen;
				for(; i<iDataLen+1; i++)  pStr[i]=0x20;  // 右边补空格
				pStr[i]=0;
			}
			else								// 小数点位数小于实际数长,左对齐
			{									// 先放置小数点前的数
				for(i=0; i<iStrLen-iPointLen; i++)  pStr[i]=pTemp[i];
				pStr[i++]='.';					// 放置小数点
				for(; i<iStrLen+1; i++)	pStr[i]=pTemp[i-1];	// 放置小数点后的数
				for(; i<iDataLen+1; i++) pStr[i]=0x20;		// 右边补空格
				pStr[i]=0;
			}
		}
		else									// 右对齐, 显示小数点
		{
			if(iPointLen >= iStrLen)			// 如果小数位数大于等于实际数长
			{
				i=0;
				if(iDataLen > iPointLen+1)		// 如果iDataLen大于小数位数+1,则左边补空格
				for(i=0; i< (iDataLen-(iPointLen+1)); i++) pStr[i]=0x20;
				pStr[i++]='0';					// 放置"0."
				pStr[i++]='.';
				j=i;							// 放置小数点后,实际数前的"0"
				for(; i<(j+iPointLen-iStrLen); i++) pStr[i]='0';
				strcpyy(pStr+i, pTemp);			// 放置实际数字
			}
			else								// 如果小数位数小于实际数长
			{
				i=0;
				if(iDataLen > iStrLen)			// 左边补空格
					for(i=0; i< (iDataLen-iStrLen); i++) pStr[i]=0x20;
				j=i; k=0;						// 放置小数点前的数
				for(; i<(j+iStrLen-iPointLen); i++, k++) pStr[i]=pTemp[k];
				pStr[i++]='.';					// 放置小数点
				j=i;							// 放置小数点后的数
				for(; i<(j+iPointLen); i++, k++) pStr[i]=pTemp[k];
				pStr[i]=0;
			}
		}
	}
	return;
}

//===========================================================================
// No more.
//===========================================================================
