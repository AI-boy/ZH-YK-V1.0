
//**--------------头文件-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------全局变量-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------






unsigned char system_run_time=0x00;   //系统运行软件定时器

unsigned int system_time_count=0x00;  

unsigned int display_lcd_time_count=0x00;
							
unsigned char display_lcd_flag=0x01;

unsigned char dat_flag=0x00;



/**********************************************************************
*函数名称：interrupt isr
*描述：中断服务程序
*返回类型：void
*输入形参：void
***********************************************************************/
//-------------------------------------------TIME0中断服务程序入口1优先级1(0,1,2,3)
void TM0_Isr() interrupt 1 using 1
{

	TF0 = 0;
	//------------------------------------------------------
					if(system_run_time==0x01)
					{
						//-----------------------------------------------------------------------------------
						system_time_count++;
					
						if(system_time_count>1000)  //1s
						{
							system_time_count=0x00;
							

							system_power_on_time_count++;
						
							if(system_power_on_time_count>=180)//180s内无按键按下则自动关机
							{
								system_power_on_time_count=0x00;
								
								POWER_OFF;
							}
																											
						}
						//---------------------------------------------------------------------------------
						scan_key_time_count++;
						
						if(scan_key_time_count>=40)    //50ms扫描按键
						{
							scan_key_time_count=0x00;
							
							handle_scan_key_flag=0x01;
						}
						//---------------------------------------------------------------------------------
						display_lcd_time_count++;
						
						if(display_lcd_time_count>=400) //500ms刷新LCD显示
						{
							display_lcd_time_count=0x00;
							
							dat_flag = dat_flag^0x01;
							
							display_lcd_flag=0x01;

						}
						//---------------------------------------------------------------------------------
						
						if(poll_time_enable)
						{
							poll_time_count++;
						
							if(poll_time_count>=1000)
							{
								poll_time_count=0x00;
								
								poll_task_flag=0x01;
							}
						}
					
						//---------------------------------------------------------------------------------
						if(beep_delay_time_count>0)
						{
							beep_delay_time_count--;

							if(beep_delay_time_count==0x00)
							{
								BEEP_OFF;
							}
						}
						
						
					}
									
					//------------------------------------------------------
		
					if (uart2_time_count > 0x00)   //UART1接受结束鉴别
					{
						uart2_time_count--;
						
						if(uart2_time_count==0)
						{
							if((uart2_receive_byte_count==54)&&(uart2_rx_buf[1]==0xB1)&&(uart2_rx_buf[53]==0xAA))
							{
								rx_frame_kind=0x01;
								
								uart2_receive_flag=TRUE;
							}
							else if((uart2_receive_byte_count==21)&&(uart2_rx_buf[1]==0xB2)&&(uart2_rx_buf[20]==0xAA))
							{
								rx_frame_kind=0x02;
								
								uart2_receive_flag=TRUE;
							}
							else if((uart2_receive_byte_count==6)&&(uart2_rx_buf[1]==0xB3)&&(uart2_rx_buf[5]==0xAA))
							{
								rx_frame_kind=0x03;
								
								uart2_receive_flag=TRUE;
							}
							else if((uart2_receive_byte_count==6)&&(uart2_rx_buf[1]==0xB4)&&(uart2_rx_buf[5]==0xAA))
							{
								rx_frame_kind=0x04;
								
								uart2_receive_flag=TRUE;
							}
							else if((uart2_receive_byte_count==6)&&(uart2_rx_buf[1]==0xB5)&&(uart2_rx_buf[5]==0xAA))
							{
								rx_frame_kind=0x05;
								
								uart2_receive_flag=TRUE;
							}
							else if((uart2_receive_byte_count==6)&&(uart2_rx_buf[1]==0xB6)&&(uart2_rx_buf[5]==0xAA))
							{
								rx_frame_kind=0x06;
								
								uart2_receive_flag=TRUE;
							}
							else
							{
										S2CON&=~S2REN;
										NOP();
										NOP();
										S2CON|=S2REN;
			
										uart2_receive_byte_count=0x00;
							}
						}
						
					}		
							    		
		
}

//-------------------------------------------UART2中断服务程序入口8优先级1(0,1,2,3)
void UART2_Isr() interrupt 8 using 1
{
	unsigned char r2_data;

    if (TX2IF)
    {
       S2CON&=~0x02;                               //清UART2发送中断标志
	   tx2_mt = 1;								   //置标志        

    }
    if (RX2IF)
    {
        S2CON&=~0x01;                              //清UART2接受中断标志
        rx2_mt = 1;

		r2_data = S2BUF;

		 uart2_time_count=0x0A;//UART1接收数据 相隔5ms即表示一帧数据的结束  9600--0x05   2400--0x0A

            if( (uart2_receive_byte_count<60)&&(uart2_receive_flag==FALSE) )
              {
                 uart2_rx_buf[uart2_receive_byte_count]=r2_data;
          
                  if(uart2_rx_buf[0]==0x55)
                    {
                       uart2_receive_byte_count++;
                    } 
               } 
    }
}

/******************************************************************************
** 函数名称 : init_interrupt
** 输入参数 : 无
** 输出参数 : 无
** 功能描述 : 初始化中断
			  使能外设中断
			  使能全局中断
** 全局变量 : 无
** 作    者 : caiwk
** 日    期 : 2018-01-31
** 修    改 : 无
** 版    本 : V1.0
*******************************************************************************/
void init_interrupt(void)
{
		
	ET0 = 1;            //使能定时器0中断

	TX1IF = 0;          //清UART1发送中断标志
	RX1IF = 0;          //清UART1接受中断标志
	ET1 = 0;		    //禁止定时器1中断
	ES  = 0;			//使能UART1中断

	S2CON&=~0x02;       //清UART2发送中断标志
	S2CON&=~0x01;       //清UART2接受中断标志
	IE2&=~ET2;		    //禁止定时器2中断
	IE2|=ES2;			//使能UART2中断

	S3CON&=~0x02;       //清UART3发送中断标志
	S3CON&=~0x01;       //清UART3接受中断标志
	IE2&=~ET3;		    //禁止定时器3中断
	IE2&=~ES3;			//使能UART3中断

	S4CON&=~0x02;       //清UART4发送中断标志
	S4CON&=~0x01;       //清UART4接受中断标志
	IE2&=~ET4;		    //禁止定时器4中断
	IE2&=~ES4;			//使能UART4中断

	EA = 1;				//使能全局中断
}
