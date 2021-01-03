//############################################################
// FILE:  Task_function.h
// Created on: 2016年8月5日
// Author: XQ
// summary: Header file  and definition
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

#ifndef Task_function_H
#define Task_function_H
#include "DSP2833x_Project.h"

typedef struct {
	    Uint16    Control_Mode;  // 控制模式  VF=1    此编码开环=2      此编码FOC=3      三霍尔=4
	    Uint16    TripFlagDMC;   //  过流 保护标志
	    Uint16    drive_car;
	    Uint16    olddrive_car;
	    Uint16    clear_PWMtripz;
	    Uint16    Run_mode;
	    Uint16    Qiehuan_count;
	    Uint16    Start_order;
	   	 }logic;

#define  logic_DEFAULTS  {0,0,0,0,0,0,0,0}


void Timer_Dpie(void);
void knob_control(void);   // 旋钮电位器控制 速度信号

#endif  // end of Task_function_H definition

//===========================================================================
// End of file.
//===========================================================================
