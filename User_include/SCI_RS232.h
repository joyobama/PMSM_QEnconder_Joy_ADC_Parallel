//############################################################
// FILE:   SCI_RS232.h
// Created on: 2016年8月11日
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

#include "DSP2833x_Project.h"

#ifndef SCI_RS232_H
#define SCI_RS232_H

typedef struct {
	    Uint16   SCI232_rxdr[8];
	    Uint16   SCI232_txdr[8];
	    Uint16    Speed_target;
	    Uint16   fact_BUS_Curr;
	    Uint16   fact_BUS_Voil;
	    Uint16   fact_Module_Temp;
	    Uint16    iq_test;
	    Uint16    id_test ;
	    Uint16    uq_test;
	    Uint16    ud_test ;
	    int16    IqRef_test;
	    Uint16   Speed_fact;
	   }Test;

#define  Test_DEFAULTS  {0,0,0,0,0,0,0,0,0,0,0,0}

void SCI_RS232TX_sen(void);
void scib_fifo_init(void);
interrupt void  scibRxFifoIsr(void);

#endif  // end of SCI_RS232.h definition

//===========================================================================
// End of file.
//===========================================================================
