//############################################################
// FILE:  SCI_RS232.c
// Created on: 2016年5月18日
// Author: XQ
// summary: SCI_RS232
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

#include "SCI_RS232.h"
#include "Timer_function.h"
#include "Task_function.h"

extern  Test           TestPare;
extern  TaskTime       TaskTimePare;
extern  logic          logicContr;

void scib_fifo_init(void)
{
   ScibRegs.SCICCR.all =0x0007;   // 1 stop bit,  No loopback
                                  // No parity,8 char bits,
                                  // async mode, idle-line protocol
   ScibRegs.SCICTL1.all =0x0003;  // enable TX, RX, internal SCICLK,
                                  // Disable RX ERR, SLEEP, TXWAKE
   SciaRegs.SCICTL2.bit.TXINTENA =1;
   ScibRegs.SCICTL2.bit.RXBKINTENA =1;
   ScibRegs.SCIHBAUD = 0x0001;
   ScibRegs.SCILBAUD =0xE7 ;  //SCI_PRD 194
   ScibRegs.SCICCR.bit.LOOPBKENA =0; // Enable loop back
   ScibRegs.SCIFFTX.all=0xC028;   // 0xC022  0xC022
   ScibRegs.SCIFFRX.all=0x0028;    //0x0024
   ScibRegs.SCIFFCT.all=0x00;

   ScibRegs.SCICTL1.all =0x0023;     // Relinquish SCI from Reset
   ScibRegs.SCIFFTX.bit.TXFIFOXRESET=1;
   ScibRegs.SCIFFRX.bit.RXFIFORESET=1;

}

 void  SCI_RS232TX_sen(void)
 {
        Uint16 i;
       if(TaskTimePare.Tim1s_flag==1)
   	{

   	TestPare.SCI232_txdr[0] = 0xaa ;
   	TestPare.SCI232_txdr[1] = TestPare.fact_BUS_Voil>>8;    //
   	TestPare.SCI232_txdr[2] = TestPare.fact_BUS_Voil  ;   //
   	TestPare.SCI232_txdr[3] = TestPare.Speed_target>>8 ;     //
   	TestPare.SCI232_txdr[4] = TestPare.Speed_target  ;   //
   	TestPare.SCI232_txdr[5]=  logicContr.Run_mode ;    //
   	TestPare.SCI232_txdr[6] = logicContr.Start_order ;
   	TestPare.SCI232_txdr[7] = 0xcc ;

   	    for(i=0; i<8; i++)
   	    {
   	      while (ScibRegs.SCIFFTX.bit.TXFFST != 0){}    // 1. 修改  寄存器 ScibRegs
   	      ScibRegs.SCITXBUF=TestPare.SCI232_txdr[i];    // Send data
   	    }
   	}
}

 interrupt void scibRxFifoIsr(void)  // SCIRXINTB_ISR
  {
     EINT;
      Uint16 i;
     for(i=0;i<8;i++)
     {
         TestPare.SCI232_rxdr[i]=ScibRegs.SCIRXBUF.all;   // Read data
     }

     ScibRegs.SCIFFRX.bit.RXFFOVRCLR=1;  // Clear Overflow flag
     ScibRegs.SCIFFRX.bit.RXFFINTCLR=1;  // Clear Interrupt flag
     PieCtrlRegs.PIEACK.all|=0x100;      // Issue PIE ack
  }

//===========================================================================
// No more.
//===========================================================================

