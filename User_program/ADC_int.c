//############################################################
// FILE:  ADC_int.c
// Created on: 2016年8月5日
// Author: XQ
// summary: ADCSampPare
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

#include "ADC_int.h"

#define CPU_CLOCK_SPEED      15.000L   // 10.000L for a 100MHz CPU clock speed
#define ADC_usDELAY 50000L

extern   ADCSamp     ADCSampPare;
extern _iq   FilK1 ;
extern _iq   FilK2 ;

 Uint16 ChSel[16]   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
 Uint16	TrigSel[16] = {5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5};
 Uint16 ACQPS[16]   = {8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8};


void   ADC_MACRO_INIT( Uint16  *ChSel_X,  Uint16 *Trigsel_X,  Uint16  *ACQPS_X)
{
	EALLOW;
	SysCtrlRegs.PCLKCR0.bit.ADCENCLK = 1;
	ADC_cal();
	EDIS;

	AdcRegs.ADCTRL3.all = 0x00E0;  /* Power up bandgap/reference/ADC circuits*/
    DELAY_US(ADC_usDELAY);         /* Delay before converting ADC channels*/

 	AdcRegs.ADCTRL1.bit.ACQ_PS = ACQPS_X[0];//定义采样时间，多少个ADCLK周期数
	AdcRegs.ADCTRL1.bit.CPS = 1;//转换时间预定标器，置1是半个始终周期
	AdcRegs.ADCTRL3.bit.ADCCLKPS =  0;//ADC时钟分频
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;        /* 0x0 Dual Sequencer Mode, 0x1 Cascaded Mode，排序模式，0是双排序模式，1是级联排序模式*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x0;//中断使能，0为关闭，1为使能
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;//复位排序器到CONV00状态
	//AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;//复位排序器到CONV00状态
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1=0x1; /* enable SOC from EPWMA trigger*///使能epwm触发信号，
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2=0x1; /* enable SOC from EPWMB trigger*///使能epwm触发信号，
	AdcRegs.ADCTRL3.bit.SMODE_SEL=0x1;//设置同步采样


	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ChSel_X[0];
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ChSel_X[1];
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ChSel_X[2];
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ChSel_X[3];
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = ChSel_X[8];
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = ChSel_X[9];
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = ChSel_X[10];
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = ChSel_X[11];

	AdcRegs.ADCMAXCONV.all=0x0033;//打开所有通道
	EDIS;

    /* Set up Event Trigger with CNT_zero enable for Time-base of EPWM1 */
    EPwm1Regs.ETSEL.bit.SOCAEN = 1;     /* Enable SOCA */
    EPwm1Regs.ETSEL.bit.SOCASEL = 2;    /* Enable period event for SOCA */
    EPwm1Regs.ETPS.bit.SOCAPRD = 1;     /* Generate SOCA on the 1st event */
	EPwm1Regs.ETCLR.bit.SOCA = 1;       /* Clear SOCA flag */

	EPwm1Regs.ETSEL.bit.SOCBEN = 1;
	EPwm1Regs.ETSEL.bit.SOCBSEL = 2;
	EPwm1Regs.ETPS.bit.SOCBPRD = 1;
	EPwm1Regs.ETCLR.bit.SOCB = 1;
}

void  ADC_SOC_int(void )
{
/*	    ChSel[0]=1;		// Dummy meas. avoid 1st sample issue Rev0 Picollo
	    ChSel[1]=1;		// ChSelect: ADC A1-> DC Bus  Current
		ChSel[2]=9;		// ChSelect: ADC B1-> Phase A Current
		ChSel[3]=8;		// ChSelect: ADC B0-> Phase B Current
		ChSel[4]=0;     // ChSelect: ADC A0-> DC Bus  Voltage
		ChSel[5]=2;		// ChSelect: ADC A2->  RP3
		ChSel[6]=3;		// ChSelect: ADC A3->  RP2
		ChSel[7]=10;	// ChSelect: ADC B2-> Phase A Voltage
		ChSel[8]=11;	// ChSelect: ADC B3-> Phase B Voltage
		ChSel[9]=12;	// ChSelect: ADC B4-> Phase C Voltage
*/
        ChSel[0]=0;     // 不用，避免第一次采样发生的错误
        ChSel[1]=1;     // A1:A相电流(ADCRESULT2)，B1:B相电流(ADCRESULT3)
        ChSel[2]=2;     // A2:D轴磁场(ADCRESULT4)，B2:Q轴磁场(ADCRESULT5)
        ChSel[3]=3;     // A3:RP3(ADCRESULT6),  B3:RP2(ADCRESULT7)
        ChSel[8]=4;     // A4:直流母线电压(ADCRESULT8)，B4:直流母线电流(ADCRESULT9)
        ChSel[9]=5;     // A5:(ADCRESULT10),B5:(ADCRESULT11)
        ChSel[10]=6;    // A6:(ADCRESULT12),B6:(ADCRESULT13)
        ChSel[11]=7;    // A7:(ADCRESULT14),B7:(ADCRESULT15)

		ADC_MACRO_INIT(ChSel,TrigSel,ACQPS) ;
}

void   ADC_Sample(void )
{

	ADCSampPare.BUS_Curr = _IQmpy(FilK2,ADCSampPare.BUS_Curr )+_IQmpy(FilK1,AdcMirror.ADCRESULT9+29-ADCSampPare.OffsetBUS_Curr);

	ADCSampPare.PhaseA_Curr = _IQmpy2 (_IQ12toIQ(AdcMirror.ADCRESULT2)-ADCSampPare.OffsetPhaseA_Curr) ;
	ADCSampPare.PhaseB_Curr = _IQmpy2 (_IQ12toIQ(AdcMirror.ADCRESULT3)-ADCSampPare.OffsetPhaseB_Curr) ;

	ADCSampPare.BUS_Voltage = _IQmpy(FilK2,ADCSampPare.BUS_Voltage )+_IQmpy(FilK1,AdcMirror.ADCRESULT8);
/*
	ADCSampPare.PhaseA_Voltage = AdcMirror.ADCRESULT7 ;
    ADCSampPare.PhaseB_Voltage = AdcMirror.ADCRESULT8 ;
    ADCSampPare.PhaseC_Voltage = AdcMirror.ADCRESULT9 ;
*/
    ADCSampPare.Fluxgate_D = _IQmpy(FilK2,AdcMirror.ADCRESULT4)+ _IQmpy(FilK1,ADCSampPare.Fluxgate_D);
    ADCSampPare.Fluxgate_Q = _IQmpy(FilK2,AdcMirror.ADCRESULT5)+ _IQmpy(FilK1,ADCSampPare.Fluxgate_Q);
//    ADCSampPare.Fluxgate_D = AdcMirror.ADCRESULT4;
//    ADCSampPare.Fluxgate_Q = AdcMirror.ADCRESULT5;

    ADCSampPare.RP3_Voltage =_IQ12toIQ (AdcMirror.ADCRESULT6) ;
    ADCSampPare.RP2_Voltage =_IQ12toIQ (AdcMirror.ADCRESULT7) ;

}


//===========================================================================
// No more.
//===========================================================================
