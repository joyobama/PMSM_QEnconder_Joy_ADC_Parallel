//############################################################
// FILE:  ADC_int.h
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


#ifndef EPWM_int_H
#define EPWM_int_H
#include "DSP2833x_Project.h"

void EPWM3_int(void);
void HVDMC_Protection(void);
void  PWMDAC_int(void);
void  Svpwm_Outpwm(void);
void START_CAR(void);
void STOP_CAR(void);
#endif  // end of EPWM_int_H definition

//===========================================================================
// End of file.
//===========================================================================
