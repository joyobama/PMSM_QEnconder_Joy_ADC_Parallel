//############################################################
// FILE:  GPIO_int.c
// Created on: 2016年6月5日
// Author: XQ
// summary:  GPIO_int
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

#include "GPIO_int.h"

 void Init_Gpio_LED(void)
 {
	 EALLOW;

	 // GPIO0      CPU运行灯     //  1 S闪烁一次
    GpioCtrlRegs.GPAMUX1.bit.GPIO6 = 0;  									// GPIO11 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO6 = 1;      // GPIO11 = output
    //  GPIO1     系统故障灯
    GpioCtrlRegs.GPAMUX1.bit.GPIO7 = 0;  									// GPIO11 = GPIO
    GpioCtrlRegs.GPADIR.bit.GPIO7 = 1;      // GPIO11 = output

    EDIS;
  }


void Init_3MotorGpio(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO0 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO1 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO2 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO3 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO4 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO5 = 1;

   GpioCtrlRegs.GPAMUX1.bit.GPIO12 =1;	// 0=GPIO,  1=TZ1,  2=SCITX-A,  3=SPISIMO-B
   GpioCtrlRegs.GPADIR.bit.GPIO12 = 0;	// 1=OUTput,  0=INput    DB9

   EDIS;
}

void Init_DACEPWMGpio(void)
{
   EALLOW;
   GpioCtrlRegs.GPAMUX1.bit.GPIO10 = 1;
   GpioCtrlRegs.GPAMUX1.bit.GPIO11 = 1;
   EDIS;
}



void  Init_QEP_Gpio(void)
{
	    EALLOW;
		//  编码器 检测角度  控制
	   GpioCtrlRegs.GPBPUD.bit.GPIO50 = 0;   // Enable pull-up on GPIO50 (EQEP1A)
	   GpioCtrlRegs.GPBPUD.bit.GPIO51 = 0;   // Enable pull-up on GPIO51 (EQEP1B)
	   GpioCtrlRegs.GPBPUD.bit.GPIO52 = 0;   // Enable pull-up on GPIO52 (EQEP1S)
	   GpioCtrlRegs.GPBPUD.bit.GPIO53 = 0;   // Enable pull-up on GPIO53 (EQEP1I)

	   GpioCtrlRegs.GPBQSEL2.bit.GPIO50 = 0;   // Sync to SYSCLKOUT GPIO50 (EQEP1A)
       GpioCtrlRegs.GPBQSEL2.bit.GPIO51 = 0;   // Sync to SYSCLKOUT GPIO51 (EQEP1B)
	   GpioCtrlRegs.GPBQSEL2.bit.GPIO52 = 0;   // Sync to SYSCLKOUT GPIO52 (EQEP1S)
	   GpioCtrlRegs.GPBQSEL2.bit.GPIO53 = 0;   // Sync to SYSCLKOUT GPIO53 (EQEP1I)

	   GpioCtrlRegs.GPBMUX2.bit.GPIO50 = 1;   // Configure GPIO50 as EQEP1A
	   GpioCtrlRegs.GPBMUX2.bit.GPIO51 = 1;   // Configure GPIO51 as EQEP1B
	   GpioCtrlRegs.GPBMUX2.bit.GPIO52 = 1;   // Configure GPIO52 as EQEP1S
       GpioCtrlRegs.GPBMUX2.bit.GPIO53 = 1;   // Configure GPIO53 as EQEP1I

	    EDIS;
}

void Init_FMQ_voice(void)
{
	    EALLOW;
		//   蜂鸣器  语音报警控制
	    GpioCtrlRegs.GPBPUD.bit.GPIO60 = 0;   									// Enable pullup on GPIO11
	    GpioDataRegs.GPBCLEAR.bit.GPIO60 = 0;
	    GpioCtrlRegs.GPBMUX2.bit.GPIO60 = 0;  									// GPIO11 = GPIO
	    GpioCtrlRegs.GPBDIR.bit.GPIO60 = 1;   									// GPIO11 = OUTputIO
	    EDIS;
}

void InitScirs232bGpio(void)
{
   EALLOW;

   GpioCtrlRegs.GPAPUD.bit.GPIO18 = 0;    // Enable pull-up for GPIO22 (SCITXDB)
   GpioCtrlRegs.GPAMUX2.bit.GPIO18 = 3;   // Configure GPIO22 for SCITXDB operation

   GpioCtrlRegs.GPAPUD.bit.GPIO19 = 0;    // Enable pull-up for GPIO23 (SCIRXDB)
   GpioCtrlRegs.GPAQSEL2.bit.GPIO19 = 3;  // Asynch input GPIO23 (SCIRXDB)
   GpioCtrlRegs.GPAMUX2.bit.GPIO19 = 3;   // Configure GPIO23 for SCIRXDB operation

    EDIS;
}



/***************************************按键IO初始化************************************************/
void Init_KEY_switch(void)
{
        EALLOW;
        //    按键1
        GpioCtrlRegs.GPCMUX2.bit.GPIO81 = 0;                                    // GPIO11 = GPIO
        GpioCtrlRegs.GPCDIR.bit.GPIO81 = 0;  // GPIO11 = inputIO
        //    按键2
        GpioCtrlRegs.GPBMUX1.bit.GPIO45 = 0;                                    // GPIO11 = GPIO
        GpioCtrlRegs.GPBDIR.bit.GPIO45 = 0;                                     // GPIO11 = inputIO
        //    按键3
        GpioCtrlRegs.GPCMUX2.bit.GPIO80= 0;                                     // GPIO11 = GPIO
        GpioCtrlRegs.GPCDIR.bit.GPIO80= 0;
        //    按键4
        GpioCtrlRegs.GPBMUX1.bit.GPIO46= 0;                                     // GPIO11 = GPIO
        GpioCtrlRegs.GPBDIR.bit.GPIO46= 0;
        //    按键5
        GpioCtrlRegs.GPBMUX1.bit.GPIO47= 0;                                     // GPIO11 = GPIO
        GpioCtrlRegs.GPBDIR.bit.GPIO47= 0;

        EDIS;
}
/***************************************12864液晶IO初始化************************************************/
void Init_LCD12864_Gpio(void)
{
	 EALLOW;
	 /***************LCD_RS*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO66 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO66 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO66=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO66=1;
	 /***************LCD_RW*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO65 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO65 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO65=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO65=1;
	 /***************LCD_EN*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO64 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO64 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO64=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO64=1;
	 /***************LCD_D0*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO79 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO79 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO79 =0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO79=1;
	 /***************LCD_D1*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO78 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO78 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO78=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO78=1;
	 /***************LCD_D2*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO77 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO77 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO77=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO77=1;
	 /***************LCD_D3*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO76 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO76 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO76=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO76=1;
	 /***************LCD_D4*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO75 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO75 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO75=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO75=1;
	 /***************LCD_D5*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO74 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO74 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO74=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO74=1;
	 /***************LCD_D6*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO73 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO73 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO73=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO73=1;
	 /***************LCD_D7*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO72 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO72 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO72=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO72=1;
	 /***************LCD_REST*********************/
	 GpioCtrlRegs.GPCMUX1.bit.GPIO70 = 0;  									// GPIO11 = GPIO
	 GpioCtrlRegs.GPCDIR.bit.GPIO70 = 1;
	 GpioCtrlRegs.GPCPUD.bit.GPIO70=0;
	 GpioDataRegs.GPCCLEAR.bit.GPIO70=1;
	 EDIS;
}


