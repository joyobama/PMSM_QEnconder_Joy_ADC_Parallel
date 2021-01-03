//############################################################
// FILE:  Timer_function.h
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

#include "DSP2833x_Device.h"

#ifndef Timer_function_H
#define Timer_function_H

typedef struct {
	    Uint16   pwmisr_conut;
	    Uint16   Tim2ms_flag ;
	    Uint16   Tim50ms_count;
        Uint16   IntClock_50ms;
        Uint16   Tim50ms_flag;
        Uint16   Tim100ms_count;
        Uint16   Tim100ms_flag;
        Uint16   Tim200ms_count;
        Uint16   Tim200ms_flag;
        Uint16   Tim1s_count;
        Uint16   Tim1s_flag ;
        Uint16   Tim1min_count;
        Uint16   Tim1min_flag ;
	   }TaskTime;

#define  TaskTime_DEFAULTS  {0,0,0,0,0,0,0,0,0,0,0}
 
void RunSystimer(void);
void CLEAR_flag(void);

#endif  // end of Timer_function_H definition

//===========================================================================
// End of file.
//===========================================================================
