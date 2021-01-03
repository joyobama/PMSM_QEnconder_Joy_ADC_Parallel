;; TI File $Revision: /main/1 $
;; Checkin $Date: July 30, 2007   10:29:23 $
;;###########################################################################
;;
;; FILE:    ADC_cal.asm
;;
;; TITLE:   2833x Boot Rom ADC Cal routine.
;;
;; Functions:
;;
;;     _ADC_cal - Copies device specific calibration data into ADCREFSEL and ADCOFFTRIM registers 
;; Notes:
;;
;;###########################################################################
;; $TI Release: DSP2833x Header Files V1.01 $
;; $Release Date: September 26, 2007 $
;;###########################################################################

    .def _ADC_cal                   ;定义代码段名称为ADC_Cal
	.asg "0x711C",   ADCREFSEL_LOC  ;ADCREFSEL寄存器在DSP的地址0x711c

;-----------------------------------------------
; _ADC_cal
;-----------------------------------------------
;-----------------------------------------------
; This is the ADC cal routine.This routine is programmed into 
; reserved memory by the factory. 0xAAAA and 0xBBBB are place- 
; holders for calibration data.  
;The actual values programmed by TI are device specific. 
;
; This function assumes that the clocks have been
; enabled to the ADC module.
;-----------------------------------------------

    .sect ".adc_cal"                ;自定义初始化段.adc_cal

_ADC_cal
    MOVW  DP,   #ADCREFSEL_LOC >> 6    ;右移6位得到数据段首地址DP=0x7100
    MOV   @28,  #0xAAAA            ; actual value may not be 0xAAAA//采用直接寻址ADCREFSEL=0x1111
    MOV   @29,  #0xBBBB             ; actual value may not be 0xBBBB//采用直接寻址ADCOFFTRIM=0x1111
    LRETR
;eof ----------
