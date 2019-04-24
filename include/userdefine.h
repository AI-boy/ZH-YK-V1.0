 #ifndef _USERDEFINE_H
 #define _USERDEFINE_H
 
 
#include	<stdio.h>
#include	<stdarg.h>
#include	<string.h>
 


//------------------------------------------------------------------------------------------------包含工程头文件
 	#include"delay.h"
	#include"interrupt.h"
	#include"led.h"
	#include"timer.h"
	#include"uart.h"
	#include"pwm.h"
	#include"Modbus.h"
	#include"lcd12864.h"
	#include"beep.h"
	#include"key.h"
	#include"ird_remote.h"
	#include"io.h"
//-------------------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------------------





//#define BIT0  0
//#define BIT1  1
//#define BIT2  2
//#define BIT3  3
//#define BIT4  4
//#define BIT5  5
//#define BIT6  6
//#define BIT7  7



#define MAC_ADDR   0x55         //红外遥控设备地址




#define uchar unsigned char
#define uint  unsigned int
#define ulong unsigned long

typedef unsigned char   BYTE ;
typedef unsigned int    WORD ;


//用户自定义define

#define   CLRWDT()         (WDT_CONTR |= 0x10)

#define   NOP()				_nop_()


#ifndef	 _bool_

typedef   enum  _bool_ {FALSE=0,TRUE=1}     BOOL;

#endif

//全局变量声明

extern unsigned int system_power_on_time_count;



















#endif