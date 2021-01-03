//############################################################
// FILE:  Axis_transform.h
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

#ifndef Axis_transform_H
#define Axis_transform_H

#include "DSP2833x_Project.h"
#include "IQmathLib.h"

typedef struct {  _iq  As;  		// Input: phase-a
				  _iq  Bs;			// Input: phase-b
				  _iq  Cs;			// Input: phase-c
				  _iq  Alpha;		// Output:  a-axis
				  _iq  Beta;		// Output:  b-axis
		 	 	} CLARKE ,*p_CLARKE ;

#define  CLARKE_DEFAULTS {0,0,0,0,0}

typedef struct {  _iq  Alpha;  		// Input:  a-axis
		 		  _iq  Beta;	 	// Input:  b-axis
		 	 	  _iq  Angle;		// Input:  angle (pu)
		 	 	  _iq  Ds;			// Output:  d-axis
		 	 	  _iq  Qs;			// Output:  q-axis
		 	 	  _iq  Sine;
		 	 	  _iq  Cosine;
		 	 	} PARK , *p_PARK ;

#define  PARK_DEFAULTS {0,0,0,0,0,0,0}

typedef struct {  _iq  Alpha;  		// Output:  d-axis
		 	 	  _iq  Beta;		// Output:  q-axis
		 	 	  _iq  Angle;		// Input:  angle (pu)
		 	 	  _iq  Ds;			// Input:  d-axis
		 	 	  _iq  Qs;			// Input:  q-axis
		 	      _iq  Sine;		// Input: Sine
		 	      _iq  Cosine;		// Input: Cosine
		 	    } IPARK , *p_IPARK;

#define  IPARK_DEFAULTS {0,0,0,0,0,0,0}

void  CLARKE_Cale(p_CLARKE  pV);
void  PARK_Cale(p_PARK pV)	 ;
void  IPARK_Cale(p_IPARK pV) ;

#endif /* Axis_transform*/
//===========================================================================
// End of file.
//===========================================================================
