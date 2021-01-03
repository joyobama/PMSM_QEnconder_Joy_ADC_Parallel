//############################################################
// FILE: Timer_function.c
// Created on: 2016年5月18日
// Author: XQ
// summary: Timer_function
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

#include "Timer_function.h"
#include "GPIO_int.h"

extern  TaskTime       TaskTimePare;
void RunSystimer(void)
{

    if(TaskTimePare.IntClock_50ms==1)
    {
        TaskTimePare.IntClock_50ms=0;
        TaskTimePare.Tim50ms_flag =1;
        if(++TaskTimePare.Tim100ms_count>=2)
        {
           TaskTimePare.Tim100ms_count=0;
           TaskTimePare.Tim100ms_flag=1;
        }
    }

    if(TaskTimePare.Tim100ms_flag==1)
    {
        if(++TaskTimePare.Tim200ms_count >=2)
        {
             TaskTimePare.Tim200ms_count=0;
             TaskTimePare.Tim200ms_flag=1;
        }
     }

    if(TaskTimePare.Tim200ms_flag==1)
    {
        if(++TaskTimePare.Tim1s_count >=5)
        {
             TaskTimePare.Tim1s_count=0;
             TaskTimePare.Tim1s_flag=1;
        }
     }

	if(TaskTimePare.Tim1s_flag == 1)
	{
	    LED1_REV;
		if(++TaskTimePare.Tim1min_count >=60)
		{
			TaskTimePare.Tim1min_count = 0;
			TaskTimePare.Tim1min_flag = 1;
		}
	}

}

void CLEAR_flag(void)
{

	TaskTimePare.Tim50ms_flag=0;
	TaskTimePare.Tim100ms_flag=0;
	TaskTimePare.Tim200ms_flag=0;
	TaskTimePare.Tim1s_flag=0;
	TaskTimePare.Tim1min_flag=0;
}


//===========================================================================
// No more.
//===========================================================================

