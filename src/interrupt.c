
//**--------------ͷ�ļ�-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------ȫ�ֱ���-----------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------






unsigned char system_run_time=0x00;   //ϵͳ���������ʱ��

unsigned int system_time_count=0x00;  

unsigned int display_lcd_time_count=0x00;
							
unsigned char display_lcd_flag=0x01;

unsigned char dat_flag=0x00;



/**********************************************************************
*�������ƣ�interrupt isr
*�������жϷ������
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
//-------------------------------------------TIME0�жϷ���������1���ȼ�1(0,1,2,3)
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
						
							if(system_power_on_time_count>=180)//180s���ް����������Զ��ػ�
							{
								system_power_on_time_count=0x00;
								
								POWER_OFF;
							}
																											
						}
						//---------------------------------------------------------------------------------
						scan_key_time_count++;
						
						if(scan_key_time_count>=40)    //50msɨ�谴��
						{
							scan_key_time_count=0x00;
							
							handle_scan_key_flag=0x01;
						}
						//---------------------------------------------------------------------------------
						display_lcd_time_count++;
						
						if(display_lcd_time_count>=400) //500msˢ��LCD��ʾ
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
		
					if (uart2_time_count > 0x00)   //UART1���ܽ�������
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

//-------------------------------------------UART2�жϷ���������8���ȼ�1(0,1,2,3)
void UART2_Isr() interrupt 8 using 1
{
	unsigned char r2_data;

    if (TX2IF)
    {
       S2CON&=~0x02;                               //��UART2�����жϱ�־
	   tx2_mt = 1;								   //�ñ�־        

    }
    if (RX2IF)
    {
        S2CON&=~0x01;                              //��UART2�����жϱ�־
        rx2_mt = 1;

		r2_data = S2BUF;

		 uart2_time_count=0x0A;//UART1�������� ���5ms����ʾһ֡���ݵĽ���  9600--0x05   2400--0x0A

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
** �������� : init_interrupt
** ������� : ��
** ������� : ��
** �������� : ��ʼ���ж�
			  ʹ�������ж�
			  ʹ��ȫ���ж�
** ȫ�ֱ��� : ��
** ��    �� : caiwk
** ��    �� : 2018-01-31
** ��    �� : ��
** ��    �� : V1.0
*******************************************************************************/
void init_interrupt(void)
{
		
	ET0 = 1;            //ʹ�ܶ�ʱ��0�ж�

	TX1IF = 0;          //��UART1�����жϱ�־
	RX1IF = 0;          //��UART1�����жϱ�־
	ET1 = 0;		    //��ֹ��ʱ��1�ж�
	ES  = 0;			//ʹ��UART1�ж�

	S2CON&=~0x02;       //��UART2�����жϱ�־
	S2CON&=~0x01;       //��UART2�����жϱ�־
	IE2&=~ET2;		    //��ֹ��ʱ��2�ж�
	IE2|=ES2;			//ʹ��UART2�ж�

	S3CON&=~0x02;       //��UART3�����жϱ�־
	S3CON&=~0x01;       //��UART3�����жϱ�־
	IE2&=~ET3;		    //��ֹ��ʱ��3�ж�
	IE2&=~ES3;			//ʹ��UART3�ж�

	S4CON&=~0x02;       //��UART4�����жϱ�־
	S4CON&=~0x01;       //��UART4�����жϱ�־
	IE2&=~ET4;		    //��ֹ��ʱ��4�ж�
	IE2&=~ES4;			//ʹ��UART4�ж�

	EA = 1;				//ʹ��ȫ���ж�
}
