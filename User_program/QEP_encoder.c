//############################################################
// FILE:  QEP_encoder.c
// Created on: 2016年6月21日
// Author: XQ
// summary:  QEP_encoder
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

#include "QEP_encoder.h"
#include "math.h"

#define PI 3.14159265358979
extern  EQEP   EQEPPare;
extern  Speed_QEP   Speed_QEPPare;
extern  float32   T;

// 由于编码器和电机是对向安装所以 将A和B信号线倒置接线

void  QEPEncoder_init(void)
{
	 EALLOW;
	EQep1Regs.QDECCTL.all = 0x0000;
	EQep1Regs.QEPCTL.all = 0x821E;	 // 8000  0200  0010  0008	0004 0002
	EQep1Regs.QPOSCTL.all = 0x0000;
	EQep1Regs.QUPRD = 1500000;		        	/* Unit Timer for 150Hz*/
	EQep1Regs.QCAPCTL.all = 0X8075;	 // 0X0005  0x0070	 8000
	EQep1Regs.QPOSMAX = 4* 1000;
	 EDIS;

	EQEPPare.Poles=4;
	EQEPPare.initial_angle=_IQ(0.558);
	Speed_QEPPare.K1 = _IQ21(1/(240*T));
	Speed_QEPPare.K2 = _IQ(1/(1+T*2*PI*5));  // Low-pass cut-off frequency
	Speed_QEPPare.K3 = _IQ(1)-Speed_QEPPare.K2;
	Speed_QEPPare.BaseRpm = 120*30;
}

void  QEPEncoder_Cale(p_EQEP  pV)
{
     pV->DirectionQep = EQep1Regs.QEPSTS.bit.QDF;
     pV->RawTheta = EQep1Regs.QPOSCNT + pV->CalibratedAngle;

     if (pV->RawTheta < 0)
     pV->RawTheta = pV->RawTheta + EQep1Regs.QPOSMAX;
     else if (pV->RawTheta > EQep1Regs.QPOSMAX)
	 pV->RawTheta = pV->RawTheta - EQep1Regs.QPOSMAX;
	 pV->MechTheta= pV->MechScaler*pV->RawTheta;
	 pV->ElecThetaYS = pV->MechTheta %_IQ(1.0);

	 // pV->ElecTheta = (pV->Poles*pV->MechTheta) - floor(pV->Poles*pV->MechTheta);
	 if (EQep1Regs.QFLG.bit.IEL == 1)
	  {
	    pV->IndexSyncFlag = 0x00F0;
	    pV->QepCountIndex = EQep1Regs.QPOSILAT;
	   EQep1Regs.QCLR.bit.IEL = 1;	/* Clear interrupt flag */
	  }
	 if(EQep1Regs.QFLG.bit.UTO == 1)
	  {
	   if((EQep1Regs.QEPSTS.bit.COEF || EQep1Regs.QEPSTS.bit.CDEF))
	  	{
	  	EQep1Regs.QEPSTS.all = 0x000C;
	   	}
	   else if(EQep1Regs.QCPRDLAT!=0xffff)
	   	pV->QepPeriod = EQep1Regs.QCPRDLAT;
	    }
}

void  Speed_QEP_Cale(p_Speed_QEP  pV)
{
    if ((pV->ElecTheta < _IQ(0.9))&(pV->ElecTheta > _IQ(0.1)))
	pV->Tmp = _IQmpy(pV->K1,(pV->ElecTheta - pV->OldElecTheta));
    else pV->Tmp = _IQtoIQ21(pV->Speed);
	pV->Tmp = _IQmpy(pV->K2,_IQtoIQ21(pV->Speed))+_IQmpy(pV->K3,pV->Tmp);
	pV->Tmp=_IQsat(pV->Tmp,_IQ21(1),_IQ21(-1));
	pV->Speed = _IQ21toIQ(pV->Tmp);
    pV->OldElecTheta = pV->ElecTheta;
    pV->SpeedRpm = _IQmpy(pV->BaseRpm,pV->Speed);
    if( pV->SpeedRpm<0  )
     pV->SpeedRpm=-pV->SpeedRpm;

}


//===========================================================================
// No more.
//===========================================================================
