//############################################################
// FILE:  PI_Cale.h
// Created on: 2016年4月11日
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

#ifndef  PI_Cale_H
#define  PI_Cale_H
#include "IQmathLib.h"

typedef struct {
	         _iq  Ref;   			// Input: reference set-point
			 _iq  Fbk;   			// Input: feedback
			 _iq  Out;   			// Output: controller output
			 _iq  OutF;
			 _iq  Kp;				// Parameter: proportional loop gain
			 _iq  Ki;			    // Parameter: integral gain
			 _iq  Umax;			    // Parameter: upper saturation limit
			 _iq  Umin;			    // Parameter: lower saturation limit
			 _iq  up;				// Data: proportional term
			 _iq  ui;				// Data: integral term
			 _iq  v1;				// Data: pre-saturated controller output
			 _iq  i1;				// Data: integrator storage: ui(k-1)
	   } PI_Control, *p_PI_Control ;

#define PI_Control_DEFAULTS {0,0,0,0,0,0,_IQ(1.0),0,0,0,0,0}

void  PI_Controller(p_PI_Control  pV);
void  PI_Pare_init(void );
#endif /* PI_Cale*/
