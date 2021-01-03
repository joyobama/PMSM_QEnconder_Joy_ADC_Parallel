//############################################################
// FILE:  Axis_transform.c
// Created on: 2016年8月11日
// Author: XQ
// summary:Axis_transform
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

#include "Axis_transform.h"

extern   CLARKE       ClarkeI;

void  CLARKE_Cale(p_CLARKE  pV)
{
	pV->Alpha = pV->As;
	pV->Beta = _IQmpy((pV->As +_IQmpy2(pV->Bs)),_IQ(0.57735026918963));
}

void  PARK_Cale(p_PARK pV)
{
	pV->Ds = _IQmpy(pV->Alpha,pV->Cosine) + _IQmpy(pV->Beta,pV->Sine);
    pV->Qs = _IQmpy(pV->Beta,pV->Cosine) - _IQmpy(pV->Alpha,pV->Sine);
}

void  IPARK_Cale(p_IPARK pV)   // pV->
{
	pV->Alpha = _IQmpy(pV->Ds,pV->Cosine) - _IQmpy(pV->Qs,pV->Sine);
	pV->Beta  = _IQmpy(pV->Qs,pV->Cosine) + _IQmpy(pV->Ds,pV->Sine);
}

//===========================================================================
// No more.
//===========================================================================

