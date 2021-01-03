//############################################################
// FILE:  KEY.h
// Created on: 2016年7月5日
// Author: XY
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

#ifndef KEY_H
#define KEY_H
#include "DSP2833x_Project.h"


typedef struct {
	    Uint16   Key_num[5];
	    Uint16   KeyDataK;
	    Uint16   Key_count[5];
	    Uint16   Key_switch[5];
	   }KEY;

#define  KEY_DEFAULTS  {0,0,0,0}

void Key_Can(void);
void Key_Dispose(void);
void Show_disp(void);
#endif


