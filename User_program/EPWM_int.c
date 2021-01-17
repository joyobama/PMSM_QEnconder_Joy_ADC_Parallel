//############################################################
// FILE:  EPWM_int.c
// Created on: 2016��6��5��
// Author: XQ
// summary:EPWM
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
	  //PWM_Deadband  =2.0*SYSTEM_FREQUENCY;//ԭ��������ʱ��Ϊ2us
	  PWM_Deadband  =4*SYSTEM_FREQUENCY;//����ʱ��Ϊ4us

	  EALLOW;
      EPwm1Regs.TBCTL.bit.SYNCOSEL = 0;//ͬ���ź�
      EPwm2Regs.TBCTL.bit.SYNCOSEL = 0;
      EPwm3Regs.TBCTL.bit.SYNCOSEL = 0;

      EPwm1Regs.TBCTL.bit.PHSEN = 1;//��λ����
      EPwm2Regs.TBCTL.bit.PHSEN = 1;
      EPwm3Regs.TBCTL.bit.PHSEN = 1;

      EPwm1Regs.TBPRD = PWM_PeriodMax;    //  6000�趨PWM����
      EPwm2Regs.TBPRD = PWM_PeriodMax;
      EPwm3Regs.TBPRD = PWM_PeriodMax;

      EPwm1Regs.TBPHS.half.TBPHS = 0;//��λ�Ĵ�������
      EPwm2Regs.TBPHS.half.TBPHS = 0;
      EPwm3Regs.TBPHS.half.TBPHS = 0;

      EPwm1Regs.TBCTL.all = 0xA00A;
      EPwm2Regs.TBCTL.all = 0xA00A;
      EPwm3Regs.TBCTL.all = 0xA00A;

      EPwm1Regs.CMPCTL.all = 0;
      EPwm2Regs.CMPCTL.all = 0;
      EPwm3Regs.CMPCTL.all = 0;

      EPwm1Regs.AQCTLA.all = 0x0090;//ԭ����
      EPwm2Regs.AQCTLA.all = 0x0090;
      EPwm3Regs.AQCTLA.all = 0x0090;//�ߵ�ƽ��Ч�������
//      EPwm1Regs.AQCTLA.all = 0x0060;//�͵�ƽ��Ч�������
//      EPwm2Regs.AQCTLA.all = 0x0060;
//      EPwm3Regs.AQCTLA.all = 0x0060;

      EPwm1Regs.DBCTL.all = 0x000B;  // 0x0003
      EPwm2Regs.DBCTL.all = 0x000B;  // ȫһ��  �͵�ƽ
      EPwm3Regs.DBCTL.all = 0x000B;//�ߵ�ƽ��Ч��ʹ���������������½�������
//      EPwm1Regs.DBCTL.all = 0x0007;  // 0x0003
//      EPwm2Regs.DBCTL.all = 0x0007;  // �͵�ƽ��Ч��ʹ���������������½�������
//      EPwm3Regs.DBCTL.all = 0x0007;

      EPwm1Regs.DBFED =  PWM_Deadband;//�½�������ʱ��
      EPwm1Regs.DBRED =  PWM_Deadband;//����������ʱ��
      EPwm2Regs.DBFED =  PWM_Deadband;
      EPwm2Regs.DBRED =  PWM_Deadband;
      EPwm3Regs.DBFED =  PWM_Deadband;
      EPwm3Regs.DBRED =  PWM_Deadband;

      EPwm1Regs.PCCTL.all = 0;//ն������
      EPwm2Regs.PCCTL.all = 0;
      EPwm3Regs.PCCTL.all = 0;

      EPwm1Regs.TZSEL.all = 0;//����trip eventʱ���������̬
      EPwm2Regs.TZSEL.all = 0;
      EPwm3Regs.TZSEL.all = 0;

      EDIS;                         /* Disable EALLOW*/
}

void HVDMC_Protection(void)
{

      EALLOW;

      EPwm1Regs.TZSEL.bit.CBC6=0x1;//enable TZ6 for CBC
      EPwm2Regs.TZSEL.bit.CBC6=0x1;//enable TZ6 for CBC
      EPwm3Regs.TZSEL.bit.CBC6=0x1;//enable TZ6 for CBC

      EPwm1Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT
      EPwm2Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT
      EPwm3Regs.TZSEL.bit.OSHT1   = 1;  //enable TZ1 for OSHT

      //ԭ���̣��ߵ�ƽ��Ч������ʱǿ�����ͣ��ضϿ��ع�
      EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
      EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low

      EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
      EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low

      EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_LO; // EPWMxA will go low
      EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_LO; // EPWMxB will go low
      //ԭ���̣��ߵ�ƽ��Ч������ʱǿ�����ͣ��ضϿ��ع�
      //ԭ���̣��ߵ�ƽ��Ч������ʱǿ�����ͣ��ضϿ��ع�
//      EPwm1Regs.TZCTL.bit.TZA = TZ_FORCE_HI; // EPWMxA will go high
//      EPwm1Regs.TZCTL.bit.TZB = TZ_FORCE_HI; // EPWMxB will go high

//      EPwm2Regs.TZCTL.bit.TZA = TZ_FORCE_HI; // EPWMxA will go high//
//      EPwm2Regs.TZCTL.bit.TZB = TZ_FORCE_HI; // EPWMxB will go high

//      EPwm3Regs.TZCTL.bit.TZA = TZ_FORCE_HI; // EPWMxA will go high
//      EPwm3Regs.TZCTL.bit.TZB = TZ_FORCE_HI; // EPWMxB will go high
      //ԭ���̣��ߵ�ƽ��Ч������ʱǿ�����ͣ��ضϿ��ع�

      EDIS;

//************************** End of Prot. Conf. ***************************//
}

void  Svpwm_Outpwm(void)
{
   EPwm1Regs.CMPA.half.CMPA = _IQmpy(PWM_HalfPerMax,Svpwmdq.Ta)+ PWM_HalfPerMax;
   EPwm2Regs.CMPA.half.CMPA = _IQmpy(PWM_HalfPerMax,Svpwmdq.Tb)+ PWM_HalfPerMax;
   EPwm3Regs.CMPA.half.CMPA = _IQmpy(PWM_HalfPerMax,Svpwmdq.Tc)+ PWM_HalfPerMax;
}

void STOP_CAR(void)           //  �����ű� ȫΪ��
{
	EALLOW;
	 EPwm1Regs.DBCTL.bit.POLSEL = 0;//ת��Ϊ�ߵ�ƽ��Ч���ǻ���ģʽ
	 EPwm2Regs.DBCTL.bit.POLSEL = 0;//ת��Ϊ�ߵ�ƽ��Ч���ǻ���ģʽ
	 EPwm3Regs.DBCTL.bit.POLSEL = 0;//ת��Ϊ�ߵ�ƽ��Ч���ǻ���ģʽ
//	 EPwm1Regs.DBCTL.bit.POLSEL = 0x3;//ת��Ϊ�͵�ƽ��Ч���ǻ���ģʽ
//	 EPwm2Regs.DBCTL.bit.POLSEL = 0x3;//ת��Ϊ�͵�ƽ��Ч���ǻ���ģʽ
//	 EPwm3Regs.DBCTL.bit.POLSEL = 0x3;//ת��Ϊ�͵�ƽ��Ч���ǻ���ģʽ

	 EPwm1Regs.AQCSFRC.all = 0x05;//����һ�����жϣ����ж�ǿ������
	 EPwm2Regs.AQCSFRC.all = 0x05;//����һ�����жϣ����ж�ǿ������
	 EPwm3Regs.AQCSFRC.all = 0x05;//����һ�����жϣ����ж�ǿ������
//	 EPwm1Regs.AQCSFRC.all = 0x06;//����һ�����жϣ����ж�ǿ����һ
//	 EPwm2Regs.AQCSFRC.all = 0x06;//����һ�����жϣ����ж�ǿ����һ
//	 EPwm3Regs.AQCSFRC.all = 0x06;//����һ�����жϣ����ж�ǿ����һ
	 EDIS;
}


void START_CAR(void)   //   �����ű� �Գƻ���
{
	EALLOW;
	 EPwm1Regs.DBCTL.bit.POLSEL = 2;//����ߵ�ƽ��Ч�������ģʽ
	 EPwm2Regs.DBCTL.bit.POLSEL = 2;//����ߵ�ƽ��Ч�������ģʽ
	 EPwm3Regs.DBCTL.bit.POLSEL = 2;//����ߵ�ƽ��Ч�������ģʽ
//	 EPwm1Regs.DBCTL.bit.POLSEL = 1;//����͵�ƽ��Ч�������ģʽ
//     EPwm2Regs.DBCTL.bit.POLSEL = 1;//����͵�ƽ��Ч�������ģʽ
//     EPwm3Regs.DBCTL.bit.POLSEL = 1;//����͵�ƽ��Ч�������ģʽ

	 EPwm1Regs.AQCSFRC.all = 0x00;//���ǿ�ƼĴ�������ǿ�ƶ�������������
	 EPwm2Regs.AQCSFRC.all = 0x00;//���ǿ�ƼĴ�������ǿ�ƶ�������������
	 EPwm3Regs.AQCSFRC.all = 0x00;//���ǿ�ƼĴ�������ǿ�ƶ�������������
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
