//############################################################
// FILE:  ADC_int.c
// Created on: 2016��8��5��
// Author: XQ
// summary: ADCSampPare
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//��Ȩ���У�����ؾ�
//DSP/STM32������ƿ�����
//˶������
//��ַ: https://shuolidianzi.taobao.com
//�޸�����:2016/5/23
//�汾��V16.3-1
//Author-QQ: 616264123
//�������QQȺ��314306105
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

 	AdcRegs.ADCTRL1.bit.ACQ_PS = ACQPS_X[0];//�������ʱ�䣬���ٸ�ADCLK������
	AdcRegs.ADCTRL1.bit.CPS = 1;//ת��ʱ��Ԥ����������1�ǰ��ʼ������
	AdcRegs.ADCTRL3.bit.ADCCLKPS =  0;//ADCʱ�ӷ�Ƶ
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 0;        /* 0x0 Dual Sequencer Mode, 0x1 Cascaded Mode������ģʽ��0��˫����ģʽ��1�Ǽ�������ģʽ*/
	AdcRegs.ADCTRL2.bit.INT_ENA_SEQ1 = 0x0;//�ж�ʹ�ܣ�0Ϊ�رգ�1Ϊʹ��
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 0x1;//��λ��������CONV00״̬
	//AdcRegs.ADCTRL2.bit.RST_SEQ2 = 0x1;//��λ��������CONV00״̬
	AdcRegs.ADCTRL2.bit.EPWM_SOCA_SEQ1=0x1; /* enable SOC from EPWMA trigger*///ʹ��epwm�����źţ�
    AdcRegs.ADCTRL2.bit.EPWM_SOCB_SEQ2=0x1; /* enable SOC from EPWMB trigger*///ʹ��epwm�����źţ�
	AdcRegs.ADCTRL3.bit.SMODE_SEL=0x1;//����ͬ������


	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = ChSel_X[0];
	AdcRegs.ADCCHSELSEQ1.bit.CONV01 = ChSel_X[1];
	AdcRegs.ADCCHSELSEQ1.bit.CONV02 = ChSel_X[2];
	AdcRegs.ADCCHSELSEQ1.bit.CONV03 = ChSel_X[3];
	AdcRegs.ADCCHSELSEQ3.bit.CONV08 = ChSel_X[8];
	AdcRegs.ADCCHSELSEQ3.bit.CONV09 = ChSel_X[9];
	AdcRegs.ADCCHSELSEQ3.bit.CONV10 = ChSel_X[10];
	AdcRegs.ADCCHSELSEQ3.bit.CONV11 = ChSel_X[11];

	AdcRegs.ADCMAXCONV.all=0x0033;//������ͨ��
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
        ChSel[0]=0;     // ���ã������һ�β��������Ĵ���
        ChSel[1]=1;     // A1:A�����(ADCRESULT2)��B1:B�����(ADCRESULT3)
        ChSel[2]=2;     // A2:D��ų�(ADCRESULT4)��B2:Q��ų�(ADCRESULT5)
        ChSel[3]=3;     // A3:RP3(ADCRESULT6),  B3:RP2(ADCRESULT7)
        ChSel[8]=4;     // A4:ֱ��ĸ�ߵ�ѹ(ADCRESULT8)��B4:ֱ��ĸ�ߵ���(ADCRESULT9)
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
