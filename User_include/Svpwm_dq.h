//############################################################
// FILE:    Svpwm_dq.h
// Created on: 2016年2月2日
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

#ifndef  Svpwm_dq_H
#define  Svpwm_dq_H
#include "DSP2833x_Project.h"
#include "IQmathLib.h"

typedef struct 	{ _iq  Ualpha; 			// Input:   alpha-axis
				  _iq  Ubeta;			// Input:   beta-axis
				  _iq  Ta;				// Output:  phase-a
				  _iq  Tb;				// Output:  phase-b
				  _iq  Tc;				// Output:  phase-c
				  _iq  tmp1;			// Variable: temp
				  _iq  tmp2;			// Variable: temp
				  _iq  tmp3;			// Variable: temp
				  Uint16 VecSector;		// Space vector sector
				} SVPWM , *p_SVPWM ;


#define SVPWM_DEFAULTS  { 0,0,0,0,0,0,0,0,0}

void  SVPWM_Cale(p_SVPWM pV);

#endif /* Svpwm_dq*/
