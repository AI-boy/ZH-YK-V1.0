
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
*函数名称：init_port
*描述：端口初始化
*返回类型：void
*输入形参：void
***********************************************************************/
void init_port(void)
{
	P0M0 = 0x00;                                //	设置P0.0~P0.7
    P0M1 = 0xff;								//	初始化为高阻输入模式

	P1M0 = 0x00;                                //
    P1M1 = 0xff;								// 初始化为高阻输入模式

	P2M0 = 0x00;                                //
    P2M1 = 0xff;								// 初始化为高阻输入模式

	P3M0 = 0x00;                                //
    P3M1 = 0xff;								//	初始化为高阻输入模式

	P4M0 = 0x00;                                //
    P4M1 = 0xff;								//	初始化为高阻输入模式

	P5M0 = 0x00;                                //
    P5M1 = 0xff;								//	初始化为高阻输入模式

	P6M0 = 0x00;                                //
    P6M1 = 0xff;								//	初始化为高阻输入模式

	P7M0 = 0x00;                                //
    P7M1 = 0xff;								//	初始化为高阻输入模式

	set_io_mode(PORT3,5,STAND);	//P3.5  双向端口 ON/OFF
	POWER_ON;
}

/**********************************************************************
*函数名称：set_io_mode
*描述：设置端口IO模式
*返回类型：void
*输入形参：void
***********************************************************************/
void set_io_mode(unsigned char port,unsigned char bit_n,unsigned char mode)
{
   switch(port)
   {
   		case 0:
				switch(mode)
				{
					case STAND		: P0M0&=~(1<<bit_n);P0M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P0M0|=(1<<bit_n);P0M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P0M0&=~(1<<bit_n);P0M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P0M0|=(1<<bit_n);P0M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 1:
				switch(mode)
				{
					case STAND		: P1M0&=~(1<<bit_n);P1M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P1M0|=(1<<bit_n);P1M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P1M0&=~(1<<bit_n);P1M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P1M0|=(1<<bit_n);P1M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 2:
				switch(mode)
				{
					case STAND		: P2M0&=~(1<<bit_n);P2M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P2M0|=(1<<bit_n);P2M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P2M0&=~(1<<bit_n);P2M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P2M0|=(1<<bit_n);P2M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 3:
				switch(mode)
				{
					case STAND		: P3M0&=~(1<<bit_n);P3M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P3M0|=(1<<bit_n);P3M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P3M0&=~(1<<bit_n);P3M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P3M0|=(1<<bit_n);P3M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 4:
				switch(mode)
				{
					case STAND		: P4M0&=~(1<<bit_n);P4M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P4M0|=(1<<bit_n);P4M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P4M0&=~(1<<bit_n);P4M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P4M0|=(1<<bit_n);P4M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 5:
				switch(mode)
				{
					case STAND		: P5M0&=~(1<<bit_n);P5M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P5M0|=(1<<bit_n);P5M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P5M0&=~(1<<bit_n);P5M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P5M0|=(1<<bit_n);P5M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 6:
				switch(mode)
				{
					case STAND		: P6M0&=~(1<<bit_n);P6M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P6M0|=(1<<bit_n);P6M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P6M0&=~(1<<bit_n);P6M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P6M0|=(1<<bit_n);P6M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;
		case 7:
				switch(mode)
				{
					case STAND		: P7M0&=~(1<<bit_n);P7M1&=~(1<<bit_n);break;   //双向端口模式
																				  
					case PP_OUT		: P7M0|=(1<<bit_n);P7M1&=~(1<<bit_n);break;	   //推挽输出模式
					
					case Z_IN		: P7M0&=~(1<<bit_n);P7M1|=(1<<bit_n);break;	   //高阻输入模式

					case OD			: P7M0|=(1<<bit_n);P7M1|=(1<<bit_n);break;	   //开漏输出模式

					default:break;
				}
				break;

		default:break;
   }

	
}


 





















