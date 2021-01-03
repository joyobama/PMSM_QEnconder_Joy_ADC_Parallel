//############################################################
// FILE:  QEP_encoder.c
// Created on: 2016年6月21日
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

#ifndef QEP_encoder_H_
#define QEP_encoder_H_
#include "IQmathLib.h"
#include "DSP2833x_Project.h"

typedef struct {
	    _iq ElecThetaYS;
	    _iq ElecTheta;        //   Electrical angle
	    _iq MechTheta;        //   Mechanical Angle
	    Uint16 DirectionQep;   //   rotation direction (Q0)
	    Uint16 QepPeriod;       //  Capture period of QEP
	    Uint32 QepCountIndex;   // Encoder counter index
	    int32 RawTheta;        //    Raw angle
	    _iq    MechScaler;      //   0.9999/total count
	    Uint16 LineEncoder;     //   Number of line encoder (Q0)
	    Uint16 Poles;       //   Number of pole pairs
	    int32 CalibratedAngle; //  Raw angular offset between encoder index and phase
	    Uint16 IndexSyncFlag;   //  Index sync status
	    _iq    initial_angle;
      } EQEP , *p_EQEP;

#define  EQEP_DEFAULTS  { 0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x00004000,0x0,4,0,0x0}

typedef struct {
      _iq ElecTheta;  	//   Electrical angle
      Uint32 DirectionQep; //  Direction of rotation
      _iq OldElecTheta;  // History, Electrical angle
      _iq Speed;      // Output: Estimated speed
      _iq BaseRpm;     	//  Base speed  Uint32
      _iq K1;       		//  Constant for differ  _iq21
      _iq K2;     		    //  Constant for low-pass filter
      _iq K3;     			//  Constant for low-pass filter
      int16 SpeedRpm; // Output : Estimated speed in rpm  int32
      _iq Tmp;				// Variable : Temp variable
    }Speed_QEP, *p_Speed_QEP ;

#define Speed_QEP_DEFAULTS {0,0,0,0,0,0,0,0,0}

void  QEPEncoder_init(void);
void  QEPEncoder_Cale(p_EQEP  pV);
void  Speed_QEP_Cale(p_Speed_QEP  pV);

#endif /* QEP_encoder*/
