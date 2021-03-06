
//**--------------头文件-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------全局变量-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------


/**********************************************************************
*函数名称：init_time0
*描述：初始化系统时基定时器 1ms
*返回类型：void
*输入形参：void
***********************************************************************/
void init_timer0(void)
{
   AUXR &= 0x7F;		//定时器时钟12T模式
   TMOD &= 0xF0;		//设置定时器模式
   TH0 = 0xF8;								   //定时器时钟频率：FOSC/12=24M/12=2MHz
   TL0 = 0x30;                                 //(65536-63536)=2000 * 1/2000000=1ms
   ET0 = 0;                                    //禁止定时器0中断
   EA = 0;									   //全局中断
   TF0=0;
   TR0 = 0;                                    //开启定时器
  
}