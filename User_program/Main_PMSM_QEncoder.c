//############################################################
// FILE:  Main_PMSM_QEncoder.c
// Created on: 2016年8月11日
// Author: XQ
// summary:  Main_PMSM_QEncoder
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

#include "Main_PMSM_QEncoder.h"
extern void SPI_init();
extern void InitSpi(void);
extern void spi_xmit(Uint16 a);
extern void send_to_SPI(short value,short offset,short number);
extern void spi_fifo_init(void);
extern void spi_init(void);

Test         TestPare=Test_DEFAULTS;
KEY          KEYPare=KEY_DEFAULTS;

EQEP        EQEPPare=EQEP_DEFAULTS;
Speed_QEP   Speed_QEPPare=Speed_QEP_DEFAULTS;
logic        logicContr=logic_DEFAULTS;
TaskTime     TaskTimePare=TaskTime_DEFAULTS;

PI_Control   pi_spd = PI_Control_DEFAULTS;
PI_Control   pi_id  = PI_Control_DEFAULTS;
PI_Control   pi_iq  = PI_Control_DEFAULTS;
SVPWM        SVPWM_Control=SVPWM_DEFAULTS;
ADCSamp      ADCSampPare=ADCSamp_DEFAULTS;
CLARKE       ClarkeI= CLARKE_DEFAULTS;
PARK         ParkI=PARK_DEFAULTS;
IPARK        IparkU=IPARK_DEFAULTS;
SVPWM        Svpwmdq=SVPWM_DEFAULTS;

//_iq   FilK1=_IQ(0.328);//上个状态的加权系数，用于状态的加权平滑
//_iq   FilK2=_IQ(0.672);//当前状态的加权系数，用于状态的加权平滑
_iq   FilK1=_IQ(0.328);
_iq   FilK2=_IQ(0.672);

unsigned char  Str1[17]={"印制电机驱动3.0\0"};
unsigned char  Str2[17]={"2021年01月17日\0"};
unsigned char  Str3[17]={"新年快乐\0"};

Uint16   PWMStart_Flag=0,BUS_Curr=0,BUS_Curr1=0;
double Fluxgate_Angle=0.0;
_iq test_var=0;
_iq fix_var=0;
_iq Angle_Max=0;
_iq Angle_Min=16767255;

interrupt void OffsetISR(void);

void main(void)
{
   InitSysCtrl();   // Initialize System Control, PLL, WatchDog, enable Peripheral Clocks
   InitPieCtrl();
   InitPieVectTable();

   //Initalize GPIO:
   Init_Gpio_LED();
   Init_3MotorGpio();
   Init_KEY_switch();
   Init_DACEPWMGpio();
   Init_QEP_Gpio( );
   //Init_FMQ_voice( );
   InitScirs232bGpio();
   Init_LCD12864_Gpio();
   //Initaliaze SPI of DAC TLV5610
   InitSpi();

   KEYPare.KeyDataK=0;
   MemCopy(&RamfuncsLoadStart, &RamfuncsLoadEnd, &RamfuncsRunStart);
   InitFlash();

   logicContr.Run_mode=2;


   EPWM3_int() ;
   PWMDAC_int();
   STOP_CAR();
   ADC_SOC_int( );
   scib_fifo_init( );
   CpuTimer0Regs.PRD.all = 30000000;   // 500MS   75 000000
   PI_Pare_init(  );
   HVDMC_Protection( );

    LCD12864_init();
    Lcd_ShowStr(0,48,Str1);
    Lcd_ShowStr(0,32,Str2);
    Lcd_ShowStr(0,16,Str3);

   QEPEncoder_init();

   EALLOW;  // This is needed to write to EALLOW protected registers
   PieVectTable.EPWM1_INT = &OffsetISR;
   PieVectTable.SCIRXINTB = &scibRxFifoIsr; //   GAI
   EDIS;    // This is needed to disable write to EALLOW protected registers

   EALLOW;
   PieCtrlRegs.PIECTRL.bit.ENPIE = 1;   // Enable the PIE block
   PieCtrlRegs.PIEIER3.bit.INTx1 = 1;   // EPWM1
   PieCtrlRegs.PIEIER9.bit.INTx3 = 1;   // SCIB RX  GAI

   //启动EPWM 1 中断
    EPwm1Regs.ETSEL.bit.INTEN = 1;   // Enable EPWM1INT generation
    EPwm1Regs.ETSEL.bit.INTSEL = 1;  // Enable interrupt CNT_zero event
    EPwm1Regs.ETPS.bit.INTPRD = 1;   // Generate interrupt on the 1st event
    EPwm1Regs.ETCLR.bit.INT = 1;     // Enable more interrupts

    IER |= M_INT3;
    IER |= M_INT9;  // GAI

    EINT;   // Enable Global interrupt INTM
    ERTM;   // Enable Global realtime interrupt DBGM

    while(1)
   {
    	RunSystimer() ;     //
        SCI_RS232TX_sen();
        Timer_Dpie();
    	CLEAR_flag();

   }
}

interrupt void MainISR(void)
{ 
    ///////////////////////////////////////////////////////
	QEPEncoder_Cale((p_EQEP)&EQEPPare);
    
	ADC_Sample(  );
	TaskTimePare.pwmisr_conut++;
	if( TaskTimePare.pwmisr_conut==25)
	{
	    TaskTimePare.pwmisr_conut=0;
        TaskTimePare.Tim2ms_flag=1;

        TaskTimePare.Tim50ms_count++;
        if( TaskTimePare.Tim50ms_count==25)
            {
            TaskTimePare.IntClock_50ms=1;
            TaskTimePare.Tim50ms_count=0;
            }

	    knob_control( );

	    TestPare.id_test= _IQtoIQ12(pi_id.Fbk );
        TestPare.iq_test= _IQtoIQ12(pi_iq.Fbk );
        TestPare.ud_test= _IQtoIQ12(IparkU.Ds );
        TestPare.uq_test= _IQtoIQ12(IparkU.Qs );

        TestPare.fact_BUS_Voil= _IQmpy(_IQ(0.244),ADCSampPare.BUS_Voltage);
        TestPare.fact_BUS_Curr= _IQmpy(_IQ(1.372),ADCSampPare.BUS_Curr);
        TestPare.Speed_fact=_IQtoIQ12( pi_spd.Fbk);
        TestPare.Speed_target=_IQtoIQ12( pi_spd.Ref);
        pi_spd.Fbk = _IQ12toIQ(  Speed_QEPPare.SpeedRpm);  //   0---4096RPM

		PI_Controller((p_PI_Control)&pi_spd);
		pi_spd.OutF= _IQmpy(FilK1,pi_spd.OutF)+_IQmpy(FilK2,pi_spd.Out);
	    send_to_SPI((short)(TestPare.Speed_fact),0,4);//                               DAC的A口为实际转速，即编码器转速
	    send_to_SPI((short)(TestPare.Speed_target),0,5);//                             DAC的B口为目标转速，即电位器给定
//	    send_to_SPI((short)(ADCSampPare.BUS_Curr),0,2);
	}

	  ClarkeI.As=ADCSampPare.PhaseA_Curr;
	  ClarkeI.Bs=ADCSampPare.PhaseB_Curr;

	  CLARKE_Cale((p_CLARKE)&ClarkeI );

	  ParkI.Alpha=ClarkeI.Alpha;
	  ParkI.Beta=ClarkeI.Beta;

	  //磁通门信号处理
//	  send_to_SPI((short)(ADCSampPare.Fluxgate_D),0,4);
//	  send_to_SPI((short)(ADCSampPare.Fluxgate_Q),0,5);
//	  Fluxgate_Angle= atan2((ADCSampPare.Fluxgate_Q-1986),(ADCSampPare.Fluxgate_D-1986));
	  Fluxgate_Angle= atan2((ADCSampPare.Fluxgate_Q-1986),(ADCSampPare.Fluxgate_D-1986));
	  Fluxgate_Angle=Fluxgate_Angle+PI;
	  test_var=((short)(Fluxgate_Angle*100)/PI+100)*83886.08;
//	  fix_var=3792000-5355000*_IQcosPU(0.0000001322*test_var)+8519000*_IQsinPU(0.0000001322*test_var)+1461000*_IQcosPU(0.0000002644*test_var)-3174000*_IQsinPU(0.0000002644*test_var);
//	  fix_var=790400-11030*test_var*test_var*test_var*test_var-47480*test_var*test_var*test_var+59410*test_var*test_var+58830*test_var;
	  fix_var=-23700*Fluxgate_Angle*Fluxgate_Angle*Fluxgate_Angle*Fluxgate_Angle+204600*Fluxgate_Angle*Fluxgate_Angle*Fluxgate_Angle-31820*Fluxgate_Angle*Fluxgate_Angle+616200*Fluxgate_Angle-21860;
	  fix_var=fix_var-3250000;
	  if(fix_var<0)
	  {
	      fix_var=fix_var+16767255;
	  }
	  send_to_SPI((short)(fix_var>>12),0,6);                                                   //G口为磁通门转子位置角
	  send_to_SPI((short)(EQEPPare.ElecTheta>>12),0,3);//                                         DAC的D口为电气转子位置
	  Angle_Max= fix_var-EQEPPare.ElecTheta;
	  send_to_SPI((short)(Angle_Max>>12),2048,7);                                               //H口为磁通门转子位置角减去光电转子位置角

//	  ParkI.Angle = EQEPPare.ElecTheta;
//	  ParkI.Angle = fix_var-75659001;
	  ParkI.Angle = fix_var;
//	  ParkI.Angle =Fluxgate_Angle;
///////////////////////////////////////////////
//	    if ((fix_var-ParkI.Angle) > Angle_Max)
//	          Angle_Max=(fix_var-ParkI.Angle);
//	      else if ((fix_var-ParkI.Angle) < Angle_Min)
//	          Angle_Min=(fix_var-ParkI.Angle);
//////////////////////////////////////////////查看他们之间的范围
	  ParkI.Sine = _IQsinPU(ParkI.Angle);
	  ParkI.Cosine = _IQcosPU(ParkI.Angle);

	  PARK_Cale((p_PARK)&ParkI);
	  send_to_SPI((short)((ParkI.Ds>>16)),2048,2);//  long数据类型直接移位就完事了。DAC的C口为Id电流，因为变量为long(32bit)，故这里只取前12bit

	  pi_id.Ref = _IQ(0.0);
	  pi_iq.Ref= pi_spd.Out;
      send_to_SPI((short)((pi_iq.Ref>>14)),2048,0);//                             DAC的A口为Iq电流给定
      send_to_SPI((short)((pi_iq.Fbk>>14)),2048,1);//                             DAC的B口为Iq电流反馈

	  pi_id.Fbk = ParkI.Ds;
	  PI_Controller((p_PI_Control)&pi_id);
	  pi_id.OutF= _IQmpy(FilK1,pi_id.OutF)+_IQmpy(FilK2,pi_id.Out);

	  pi_iq.Fbk = ParkI.Qs;
	  PI_Controller((p_PI_Control)&pi_iq);
	  pi_iq.OutF= _IQmpy(FilK1,pi_iq.OutF)+_IQmpy(FilK2,pi_iq.Out);

	  if(logicContr.Run_mode==1)
        {
         IparkU.Ds=0;   // 采用速度闭环  id电流闭环
         IparkU.Qs= pi_spd.Ref;  //
        }

        if(logicContr.Run_mode==2)
       {
          IparkU.Ds= pi_id.OutF;   // 采用速度闭环  id电流闭环
          IparkU.Qs= pi_spd.OutF;  //
       }
      if(logicContr.Run_mode==3)
       {
          IparkU.Ds= -pi_id.OutF;   // 采用速度闭环  id电流闭环
          IparkU.Qs= -pi_spd.OutF;  //
       }


	  IparkU.Sine   = ParkI.Sine;
	  IparkU.Cosine = ParkI.Cosine;

	  EQEPPare.ElecTheta= EQEPPare.ElecThetaYS + EQEPPare.initial_angle;
	  if( EQEPPare.ElecTheta > _IQ(1.0))
		  EQEPPare.ElecTheta-= _IQ(1.0) ;
	  else if( EQEPPare.ElecTheta < _IQ(0.0))
		  EQEPPare.ElecTheta+=_IQ(1.0);

//	  Speed_QEPPare.ElecTheta =EQEPPare.ElecTheta;
	  Speed_QEPPare.ElecTheta =fix_var;
//	  Speed_QEPPare.DirectionQep = (int32)(EQEPPare.DirectionQep);
	  Speed_QEPPare.DirectionQep = 0;
	  Speed_QEP_Cale((p_Speed_QEP)&Speed_QEPPare);

	  IPARK_Cale((p_IPARK)&IparkU);

	  Svpwmdq.Ualpha = IparkU.Alpha;
	  Svpwmdq.Ubeta = IparkU.Beta;

	  SVPWM_Cale((p_SVPWM)&Svpwmdq);

	  Svpwm_Outpwm();

	  EPwm6Regs.CMPA.half.CMPA= TestPare.Speed_target ;// Hall_Three.ele_angleIQ  _IQtoIQ12(Angle_SMOPare.Theta )  ;
	  EPwm6Regs.CMPB = _IQtoIQ12(Svpwmdq.Tc ) ;// _IQtoIQ12(VF_AnglePare.Angle_theta )  ;
	// Enable more interrupts from this timer
	EPwm1Regs.ETCLR.bit.INT = 1;

	// Acknowledge interrupt to recieve more interrupts from PIE group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}

interrupt void OffsetISR(void)
{
   TaskTimePare.pwmisr_conut++;
   if (TaskTimePare.pwmisr_conut>=5000)
	   {
	   ADCSampPare.OffsetBUS_Curr= _IQmpy( ADCSampPare.Coeff_filterK1,ADCSampPare.OffsetBUS_Curr)+_IQmpy(ADCSampPare.Coeff_filterK2, AdcMirror.ADCRESULT9 );		// Bus DC  offset
	   ADCSampPare.OffsetPhaseA_Curr= _IQmpy(ADCSampPare.Coeff_filterK1,ADCSampPare.OffsetPhaseA_Curr)+_IQmpy(ADCSampPare.Coeff_filterK2,_IQ12toIQ(AdcMirror.ADCRESULT2));	//Phase U offset
	   ADCSampPare.OffsetPhaseB_Curr= _IQmpy(ADCSampPare.Coeff_filterK1,ADCSampPare.OffsetPhaseB_Curr)+_IQmpy(ADCSampPare.Coeff_filterK2,_IQ12toIQ(AdcMirror.ADCRESULT3));	//Phase V offset
       }

   if (TaskTimePare.pwmisr_conut>10000)
	  {
		EALLOW;
		PieVectTable.EPWM1_INT = &MainISR;
		EDIS;
	  }
	// Enable more interrupts from this timer
	EPwm1Regs.ETCLR.bit.INT = 1;
	// Acknowledge interrupt to recieve more interrupts from PIE group 3
	PieCtrlRegs.PIEACK.all = PIEACK_GROUP3;
}






//===========================================================================
// No more.
//===========================================================================

