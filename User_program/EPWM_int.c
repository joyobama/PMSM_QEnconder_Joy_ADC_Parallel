//############################################################
// FILE:  EPWM_int.c
// Created on: 2016年6月5日
// Author: XQ
// summary:EPWM
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

#include "EPWM_int.h"
#include "Svpwm_dq.h"

#define ISR_FREQUENCY     12.5
#define SYSTEM_FREQUENCY  150

extern  SVPWM        Svpwmdq;

float32 T = 0.001/ISR_FREQUENCY;

Uint16   PWM_PeriodMax=0, PWM_HalfPerMax=0 ,PWM_Deadband=0 ;

void EPWM3_int(void)
{
	  PWM_PeriodMax=SYSTEM_FREQUENCY*1000000*T/2;
	  PWM_HalfPerMax=PWM_PeriodMax/2;
	  PWM_Deadband  =2.0*SYSTEM_FREQUENCY;
	  EALLOW;
      EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;
      EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;
      EPwm3Regs.TBCTL.bit.SYNCOSEL = 0;

      EPwm1Regs.TBCTL.bit.PHSEN = 1;
      EPwm2Regs.TBCTL.bit.PHSEN = 1;
      EPwm3Regs.TBCTL.bit.PHSEN = 1;

      EPwm1Regs.TBPRD = PWM_PeriodMax;    //  6000
      EPwm2Regs.TBPRD = PWM_PeriodMax;
      EPwm3Regs.TBPRD = PWM_PeriodMax;

      EPwm1Regs.TBPHS.half.TBPHS = 0;
      EPwm2Regs.TBPHS.half.TBPHS = 0;
      EPwm3Regs.TBPHS.half.TBPHS = 0;

      EPwm1Regs.TBCTL.all = 0xA00A;
      EPwm2Regs.TBCTL.all = 0xA00A;
      EPwm3Regs.TBCTL.all = 0xA00A;

      EPwm1Regs.CMPCTL.all = 0;
      EPwm2Regs.CMPCTL.all = 0;
      EPwm3Regs.CMPCTL.all = 0;

      EPwm1Regs.AQCTLA.all = 0x0090;
      EPwm2Regs.AQCTLA.all = 0x0090;
      EPwm3Regs.AQCTLA.all = 0x0090;

      EPwm1Regs.DBCTL.all = 0x000B;  // 0x0003
      EPwm2Regs.DBCTL.all = 0x000B;  // 全一致  低电平
      EPwm3Regs.DBCTL.all = 0x000B;

      EPwm1Regs.DBFED =  PWM_Deadband;
      EPwm1Regs.DBRED =  PWM_Deadband;
      EPwm2Regs.DBFED =  PWM_Deadband;
      EPwm2Regs.DBRED =  PWM_Deadband;
      EPwm3Regs.DBFED =  PWM_Deadband;
      EPwm3Regs.DBRED =  PWM_Deadband;

      EPwm1Regs.PCCTL.all = 0;
      EPwm2Regs.PCCTL.all = 0;
      EPwm3Regs.PCCTL.all = 0;

      EPwm1Regs.TZSEL.all = 0;
      EPwm2Regs.TZSEL.all = 0;
      EPwm3Regs.TZSEL.all = 0;

      EDIS;                         /* Disable EALLOW*/
}

void HVDMC_Protection(void)
{

      EALLOW;

      EPwm1Regs.TZSEL.bit.CBC6=0x1;
      EPwm2Regs.TZSEL.bit.CBC6=0x1;
      EPwm3Regs.TZSEL.bit.CBC6=0x1;

      EPwm1Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT
      EPwm2Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT
      EPwm3Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT

      EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
      EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low

      EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
      EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low

      EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
      EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low

      EDIS;

//************************** End of Prot. Conf. ***************************//
}

void  Svpwm_Outpwm(void)
{
   EPwm1Regs.CMPA.half.CMPA = _IQmpy(PWM_HalfPerMax,Svpwmdq.Ta)+ PWM_HalfPerMax;
   EPwm2Regs.CMPA.half.CMPA = _IQmpy(PWM_HalfPerMax,Svpwmdq.Tb)+ PWM_HalfPerMax;
   EPwm3Regs.CMPA.half.CMPA = _IQmpy(PWM_HalfPerMax,Svpwmdq.Tc)+ PWM_HalfPerMax;
}

void STOP_CAR(void)           //  上下桥臂 全为低
{
	EALLOW;
	 EPwm1Regs.DBCTL.bit.POLSEL = 0;
	 EPwm2Regs.DBCTL.bit.POLSEL = 0;
	 EPwm3Regs.DBCTL.bit.POLSEL = 0;

	 EPwm1Regs.AQCSFRC.all = 0x05;
	 EPwm2Regs.AQCSFRC.all = 0x05;
	 EPwm3Regs.AQCSFRC.all = 0x05;
	 EDIS;
}


void START_CAR(void)   //   上下桥臂 对称互补
{
	EALLOW;
	 EPwm1Regs.DBCTL.bit.POLSEL = 2;
	 EPwm2Regs.DBCTL.bit.POLSEL = 2;
	 EPwm3Regs.DBCTL.bit.POLSEL = 2;

	 EPwm1Regs.AQCSFRC.all = 0x00;
	 EPwm2Regs.AQCSFRC.all = 0x00;
	 EPwm3Regs.AQCSFRC.all = 0x00;
	EDIS;
}

void  PWMDAC_int(void)
{
   EALLOW;

       EPwm6Regs.TBCTL.bit.SYNCOSEL = 0;
       EPwm6Regs.TBCTL.bit.PHSEN = 1;
       EPwm6Regs.TBPRD =4000;
       EPwm6Regs.TBPHS.half.TBPHS = 0;
       EPwm6Regs.TBCTL.all = 0xA00A;
       EPwm6Regs.CMPCTL.all = 0x0000;
       EPwm6Regs.AQCTLA.all = 0x0090;
       EPwm6Regs.AQCTLB.all = 0x0900;
       EPwm6Regs.DBCTL.all = 0x0000 ;
       EPwm6Regs.PCCTL.all = 0x0000;
       EPwm6Regs.TZSEL.all = 0x0000;
       EPwm6Regs.TZCTL.all = 0x0000;
    EDIS;
}

//===========================================================================
// No more.
//===========================================================================
