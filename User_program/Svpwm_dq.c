//############################################################
// FILE:  Svpwm_dq.c
// Created on: 2016年5月18日
// Author: XQ
// summary: Svpwm_dq
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

#include "Svpwm_dq.h"


void  SVPWM_Cale(p_SVPWM  pV)
{
    pV->tmp1= pV->Ubeta;															\
	pV->tmp2= _IQdiv2(pV->Ubeta) + (_IQmpy(_IQ(0.866),pV->Ualpha));					\
    pV->tmp3= pV->tmp2 - pV->tmp1;													\
																				\
	pV->VecSector=3;																\
	pV->VecSector=(pV->tmp2> 0)?( pV->VecSector-1):pV->VecSector;						\
	pV->VecSector=(pV->tmp3> 0)?( pV->VecSector-1):pV->VecSector;						\
	pV->VecSector=(pV->tmp1< 0)?(7-pV->VecSector) :pV->VecSector;						\
																				\
	if     (pV->VecSector==1 || pV->VecSector==4)                                   \
      {     pV->Ta= pV->tmp2; 														\
      		pV->Tb= pV->tmp1-pV->tmp3; 												\
      		pV->Tc=-pV->tmp2;														\
      }								    										\
   																				\
    else if(pV->VecSector==2 || pV->VecSector==5)                                   \
      {     pV->Ta= pV->tmp3+pV->tmp2; 												\
      		pV->Tb= pV->tmp1; 														\
      		pV->Tc=-pV->tmp1;														\
      }																	   		\
   																				\
    else                                                                        \
      {     pV->Ta= pV->tmp3; 														\
      		pV->Tb=-pV->tmp3; 														\
      		pV->Tc=-(pV->tmp1+pV->tmp2);												\
      }																	   		\
}

//===========================================================================
// No more.
//===========================================================================
