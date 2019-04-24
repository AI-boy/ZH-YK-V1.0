//**--------------ͷ�ļ�-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------ȫ�ֱ���-----------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------


unsigned char tx1_mt=0x00;   //UART1���ͼĴ���������ɱ�־

unsigned char tx2_mt=0x00;	 //UART2���ͼĴ���������ɱ�־

unsigned char tx3_mt=0x00;	 //UART3���ͼĴ���������ɱ�־

unsigned char tx4_mt=0x00;	 //UART4���ͼĴ���������ɱ�־

unsigned char rx1_mt=0x00;   //UART1���ܼĴ���������ɱ�־

unsigned char rx2_mt=0x00;	 //UART2���ܼĴ���������ɱ�־

unsigned char rx3_mt=0x00;	 //UART3���ܼĴ���������ɱ�־

unsigned char rx4_mt=0x00;	 //UART4���ܼĴ���������ɱ�־


unsigned char uart2_rx_buf[80];

unsigned char uart2_tx_buf[80];

unsigned char rx_frame_kind=0x00;  //����֡ ���  01--��������֡		02--��������֡		03--�������淵��ȷ��֡
unsigned char tx_frame_kind=0x00; //����֡									  





unsigned char uart2_time_count=0x00;

unsigned char uart2_receive_byte_count=0;

unsigned char uart2_receive_flag=0;







//**--------------�궨��-------------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------






/**********************************************************************
*�������ƣ�init_uart2
*������uart2��ʼ�� ������2400 8 1 N
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void init_uart2(void)
{

	set_io_mode(PORT1,1,PP_OUT);	//P1.1  TX2   �������ģʽ
	set_io_mode(PORT1,0,STAND);	    //P1.0  RX2   ��׼˫��˿ڣ�Ĭ�ϣ�

	S2CON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0x3C;		    //�趨��ʱ��ֵ
	T2H = 0xF6;		    //�趨��ʱ��ֵ
	IE2&=~ET2;		    //��ֹ��ʱ��2�ж�
	IE2&=~ES2;			//��ֹUART2�ж�

	AUXR |= 0x10;		//������ʱ��2


}

/**********************************************************************
*�������ƣ�uart2_send_byte
*������
*�������ͣ�void
*�����βΣ�BYTE  data
***********************************************************************/
void uart2_send_byte(unsigned char dat)
{  

  tx2_mt = 0; 	         //!!!

  #if defined(IRD_BY_UART)	
		Enable_pwm();	
  #endif

  S2BUF = dat;

  while (!tx2_mt);

  #if defined(IRD_BY_UART)
		Disable_pwm();
  #endif

  tx2_mt = 0;	  		 //!!!
}


/**********************************************************************
*�������ƣ�uart2_send_nbyte
*������
*�������ͣ�void
*�����βΣ�BYTE *data,WORD size
***********************************************************************/
void uart2_send_nbyte(unsigned char *dat,unsigned int size)
{
	while (size)
    {
    	uart2_send_byte(*dat);
    	dat++;
    	size--;
    }
}

/**********************************************************************
*�������ƣ�uart2_read_byte
*������
*�������ͣ�BYTE 
*�����βΣ�void
***********************************************************************/
unsigned char uart2_read_byte(void)
{
	unsigned char dat;

	rx2_mt = 0;

	while (!rx2_mt); // �ȴ����ջ�������

	rx2_mt = 0;

	dat = S2BUF;

  	return dat;
}

/**********************************************************************
*�������ƣ�uart1_read_nbyte
*������
*�������ͣ�void 
*�����βΣ�BYTE *buffer,BYTE length
***********************************************************************/
void uart2_read_nbyte(unsigned char *buffer,unsigned char length)
{
  	unsigned char i;
  	unsigned char dat;

  	for (i = 0; i < length; i++)
  	{
    	dat = uart2_read_byte(); // Get a character from the USART and save in the string
    	*buffer = dat;
    	buffer++; // Increment the string pointer
  	}
}


/**********************************************************************
*�������ƣ�uart1_read_nbyte
*������
*�������ͣ�void 
*�����βΣ�BYTE *buffer,BYTE length
*----��żУ��--------
*----żУ��(%2)--
*----��У��(/2)-----
***********************************************************************/

bit handle_even_check(unsigned char databyte)
{
	unsigned char i=0;
	
	unsigned char num=0;
	
	num=0x00;//----!!!!!!!!!!!!!!�ֲ�������������
	
	for(i=0;i<8;i++)
	{
		if(databyte&(1<<i))
		{
			num++;
		}
	}
	
	return ((bit)(num%2));


}


/**********************************************************************
*�������ƣ�handle_uart_rx_buf
*������
*�������ͣ�void 
*�����βΣ�void
***********************************************************************/

void handle_uart2_rx_buf(void)
{
	unsigned char i=0;
	
	unsigned int crc_in;
	
	if(rx_frame_kind==tx_frame_kind)
	{
		switch(rx_frame_kind)
		{
			case 0x01:  //��������
					if(uart2_rx_buf[1]==0xB1)
					{
						crc_in=crc16(&uart2_rx_buf[1],50);
						
						if(crc_in==( (uart2_rx_buf[51]<<8) | uart2_rx_buf[52]) )
						{
							p_v 		= (uart2_rx_buf[2]<<8) | uart2_rx_buf[3];
							
							b_v 		= (uart2_rx_buf[4]<<8) | uart2_rx_buf[5];
							
							load_v 		= (uart2_rx_buf[6]<<8) | uart2_rx_buf[7];
							
							charge_I 	= (uart2_rx_buf[8]<<8) | uart2_rx_buf[9];
							
							load_I		= (uart2_rx_buf[10]<<8) | uart2_rx_buf[11];
							
							sys_mode	= uart2_rx_buf[12];
							
							charge_current_value		= (uart2_rx_buf[13]<<8) | uart2_rx_buf[14];
							
							discharge_current_value		= (uart2_rx_buf[15]<<8) | uart2_rx_buf[16];
							
							temperature_value		= (uart2_rx_buf[17]<<8) | uart2_rx_buf[18];									
							
							//----------------------------------------------------------------	
							bt_00_hv = (uart2_rx_buf[19]<<8) | uart2_rx_buf[20];
							bt_00_lv = (uart2_rx_buf[21]<<8) | uart2_rx_buf[22];	
							
							bt_01_hv = (uart2_rx_buf[23]<<8) | uart2_rx_buf[24];
							bt_01_lv = (uart2_rx_buf[25]<<8) | uart2_rx_buf[26];
							
							bt_02_hv = (uart2_rx_buf[27]<<8) | uart2_rx_buf[28];
							bt_02_lv = (uart2_rx_buf[29]<<8) | uart2_rx_buf[30];
							
							bt_03_hv = (uart2_rx_buf[31]<<8) | uart2_rx_buf[32];
							bt_03_lv = (uart2_rx_buf[33]<<8) | uart2_rx_buf[34];
							
							bt_04_hv = (uart2_rx_buf[35]<<8) | uart2_rx_buf[36];
							bt_04_lv = (uart2_rx_buf[37]<<8) | uart2_rx_buf[38];
							
							bt_05_hv = (uart2_rx_buf[39]<<8) | uart2_rx_buf[40];
							bt_05_lv = (uart2_rx_buf[41]<<8) | uart2_rx_buf[42];	
							
							bt_06_hv = (uart2_rx_buf[43]<<8) | uart2_rx_buf[44];
							bt_06_lv = (uart2_rx_buf[45]<<8) | uart2_rx_buf[46];	
							
							bt_07_hv = (uart2_rx_buf[47]<<8) | uart2_rx_buf[48];
							bt_07_lv = (uart2_rx_buf[49]<<8) | uart2_rx_buf[50];
							
							bt_dy[0] = bt_00_hv;
							bt_dy[1] = bt_00_lv;
							
							bt_dy[2] = bt_01_hv;
							bt_dy[3] = bt_01_lv;
							
							bt_dy[4] = bt_02_hv;
							bt_dy[5] = bt_02_lv;
							
							bt_dy[6] = bt_03_hv;
							bt_dy[7] = bt_03_lv;
							
							bt_dy[8] = bt_04_hv;
							bt_dy[9] = bt_04_lv;
							
							bt_dy[10] = bt_05_hv;
							bt_dy[11] = bt_05_lv;
							
							bt_dy[12] = bt_06_hv;
							bt_dy[13] = bt_06_lv;
							
							bt_dy[14] = bt_07_hv;
							bt_dy[15] = bt_07_lv;	
							
							BEEP_SPEAK();
						}
					}
					break;
			
			case 0x02:
					if(uart2_rx_buf[1]==0xB2)
					{
						crc_in=crc16(&uart2_rx_buf[1],17);
						
						if(crc_in==( (uart2_rx_buf[18]<<8) | uart2_rx_buf[19]) )
						{
							light_pv 		= (uart2_rx_buf[2]<<8) | uart2_rx_buf[3];
							
							load_cc_I		= (uart2_rx_buf[4]<<8) | uart2_rx_buf[5];
							
							step_01_load_percent 	= uart2_rx_buf[6];
							
							step_02_load_percent 	= uart2_rx_buf[7];
							
							step_03_load_percent 	= uart2_rx_buf[8];
							
							step_04_load_percent 	= uart2_rx_buf[9];
							
							step_05_load_percent 	= uart2_rx_buf[10];
							
							bt_id					= uart2_rx_buf[11];
							
							light_time				= uart2_rx_buf[12];
							
							step_01_time_limit 	= uart2_rx_buf[13];
							
							step_02_time_limit 	= uart2_rx_buf[14];
							
							step_03_time_limit 	= uart2_rx_buf[15];
							
							step_04_time_limit 	= uart2_rx_buf[16];
							
							step_05_time_limit 	= uart2_rx_buf[17];
							
							BEEP_SPEAK();
						}
					}
					break;
			
			case 0x03:
					if(uart2_rx_buf[1]==0xB3)
					{
						crc_in=crc16(&uart2_rx_buf[1],2);
						
						if(crc_in==( (uart2_rx_buf[3]<<8) | uart2_rx_buf[4]) )
						{
							set_status 		= uart2_rx_buf[2];	
							
							if(set_status==0x01)
							{		 			 	
								display_string_8x16(5,0,"....Save OK!....");
								
								delay_ms(1000);
								
								clear_screen();
								display_canshu();
							}
							else
							{
								display_string_8x16(5,0,"...Set error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_canshu();
							}																			
						}
						else
						{
								display_string_8x16(5,0,"...CRC error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_canshu();
						}
					}
					break;
			case 0x04:
					if(uart2_rx_buf[1]==0xB4)
					{
						crc_in=crc16(&uart2_rx_buf[1],2);
						
						if(crc_in==( (uart2_rx_buf[3]<<8) | uart2_rx_buf[4]) )
						{
							set_status 		= uart2_rx_buf[2];	
							
							if(set_status==0x01)
							{	
								clear_screen();
																	 			 	
								display_string_8x16(1,0,"<<Handle mode!>>");
								
								display_string_8x16(5,0,"....charging!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
							}
							else
							{
								clear_screen();
								
								display_string_8x16(5,0,"...Set error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
							}																			
						}
						else
						{
								clear_screen();
								
								display_string_8x16(5,0,"...CRC error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
						}
					}
					break;
			case 0x05:
					if(uart2_rx_buf[1]==0xB5)
					{
						crc_in=crc16(&uart2_rx_buf[1],2);
						
						if(crc_in==( (uart2_rx_buf[3]<<8) | uart2_rx_buf[4]) )
						{
							set_status 		= uart2_rx_buf[2];	
							
							if(set_status==0x01)
							{	
								clear_screen();
																	 			 	
								display_string_8x16(1,0,"<<Handle mode!>>");
								
								display_string_8x16(5,0,"..discharging!..");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
							}
							else
							{
								clear_screen();
								
								display_string_8x16(5,0,"...Set error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
							}																			
						}
						else
						{
								clear_screen();
								
								display_string_8x16(5,0,"...CRC error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
						}
					}
					break;
			case 0x06:
					if(uart2_rx_buf[1]==0xB6)
					{
						crc_in=crc16(&uart2_rx_buf[1],2);
						
						if(crc_in==( (uart2_rx_buf[3]<<8) | uart2_rx_buf[4]) )
						{
							set_status 		= uart2_rx_buf[2];	
							
							if(set_status==0x01)
							{	
								clear_screen();
																	 			 	
								display_string_8x16(1,0," <<Auto mode!>> ");
								
								display_string_8x16(5,0,"....working!....");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
							}
							else
							{
								clear_screen();
								
								display_string_8x16(5,0,"...Set error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
							}																			
						}
						else
						{
								clear_screen();
								
								display_string_8x16(5,0,"...CRC error!...");
								
								delay_ms(1000);
								
								clear_screen();
								display_run_data();
						}
					}
					break;
			default:break;
		}
	}
	
	memset (uart2_rx_buf,0,sizeof(uart2_rx_buf));
}

//---------------------------------��ȡ���������������ݡ�
void read_run_data(void)
{
	tx_frame_kind=0x01;
							     							  						         
	uart2_tx_buf[0]=0x55;
						         
	uart2_tx_buf[1]=0xA1;
						         
	crc_data=crc16(&uart2_tx_buf[1],1);
						         
	uart2_tx_buf[2]=crc_data/256;
						         
	uart2_tx_buf[3]=crc_data%256;
						         
	uart2_tx_buf[4]=0xAA;
						         
	uart2_send_nbyte(uart2_tx_buf,5);
	
}

//��ȡ��������ϵͳ������
void read_sys_parameter(void)
{
	tx_frame_kind=0x02;
				         
	uart2_tx_buf[0]=0x55;
							         
	uart2_tx_buf[1]=0xA2;
							         
	crc_data=crc16(&uart2_tx_buf[1],1);
							         
	uart2_tx_buf[2]=crc_data/256;
							         
	uart2_tx_buf[3]=crc_data%256;
							         
	uart2_tx_buf[4]=0xAA;
							         
	uart2_send_nbyte(uart2_tx_buf,5);
	
}
//���桰ϵͳ������
void save_sys_parameter(void)
{

	IapErase(0x0400);	   //����0x0400��ʼ���� 512���ֽ�
	//-----------------------------------------------------------����EEPROM������־
	IapProgram(0x0412, 0x55);  //---EEPROM ��ʼ����־λ
	//-----------------------------------------------------------�����ص�ѹ����
	IapProgram(0x0400,(unsigned char)(light_pv/256));
			
	IapProgram(0x0401,(unsigned char)light_pv);
								
	//-----------------------------------------------------------���渺�ع�����������
	IapProgram(0x0402,(unsigned char)(load_cc_I/256));
			
	IapProgram(0x0403,(unsigned char)load_cc_I);
								
	//-----------------------------------------------------------�����������ٷֱȲ���
	IapProgram(0x0404,(unsigned char)(step_01_load_percent));
								
	IapProgram(0x0405,(unsigned char)(step_02_load_percent));
								
	IapProgram(0x0406,(unsigned char)(step_03_load_percent));
								
	IapProgram(0x0407,(unsigned char)(step_04_load_percent));
								
	IapProgram(0x0408,(unsigned char)(step_05_load_percent));
								
	IapProgram(0x040a,(unsigned char)(bt_id));
								
	IapProgram(0x040b,(unsigned char)(light_time));
								
	IapProgram(0x040c,(unsigned char)(step_01_time_limit));
								
	IapProgram(0x040d,(unsigned char)(step_02_time_limit));
								
	IapProgram(0x040e,(unsigned char)(step_03_time_limit));
								
	IapProgram(0x040f,(unsigned char)(step_04_time_limit));
								
	IapProgram(0x0410,(unsigned char)(step_05_time_limit));
	
	//---------------------------------------------------------���Ͳ�����������							
	tx_frame_kind=0x03;
				         
	uart2_tx_buf[0]=0x55;
							         
	uart2_tx_buf[1]=0xA3;
							         
	uart2_tx_buf[2]=(unsigned char )(light_pv/256);
							         
	uart2_tx_buf[3]=(unsigned char )light_pv;
							         
	uart2_tx_buf[4]=(unsigned char )(load_cc_I/256);	
							         
	uart2_tx_buf[5]=(unsigned char )load_cc_I;
							         
	uart2_tx_buf[6]=(unsigned char )(step_01_load_percent);	
	
	uart2_tx_buf[7]=(unsigned char )(step_02_load_percent);	
	
	uart2_tx_buf[8]=(unsigned char )(step_03_load_percent);	
	
	uart2_tx_buf[9]=(unsigned char )(step_04_load_percent);
	
	uart2_tx_buf[10]=(unsigned char )(step_05_load_percent);
	
	uart2_tx_buf[11]=(unsigned char )(bt_id);	
	
	uart2_tx_buf[12]=(unsigned char )(light_time);
	
	uart2_tx_buf[13]=(unsigned char )(step_01_time_limit);	
	
	uart2_tx_buf[14]=(unsigned char )(step_02_time_limit);	
	
	uart2_tx_buf[15]=(unsigned char )(step_03_time_limit);	
	
	uart2_tx_buf[16]=(unsigned char )(step_04_time_limit);
	
	uart2_tx_buf[17]=(unsigned char )(step_05_time_limit);
					   
							         
	crc_data=crc16(&uart2_tx_buf[1],17);
							         
	uart2_tx_buf[18]=crc_data/256;
							         
	uart2_tx_buf[19]=crc_data%256;
							         
	uart2_tx_buf[20]=0xAA;
							         
	uart2_send_nbyte(uart2_tx_buf,21);
	
}