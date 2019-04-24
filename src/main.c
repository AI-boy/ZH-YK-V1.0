/******************************************************************************
**                           ־����ҵ���޹�˾
**
**                           
**
**--------------�����ļ���Ϣ---------------------------------------------------
** ��   ��   ��	: main.c
** ��ǰ    �汾	: V1.0 
** ��        �� : ң����������
** ��   ��   �� : kei c51
** Ӳ        �� : ZH-YK-001  STC8A4K60S
**--------------��ʷ�汾��Ϣ---------------------------------------------------
** ��ʼ��������	: 2018-06-13
** ��   ��   ��	: ��ά��
** ��  	     �� : V1.0
** �衡      �� : 

**-----------------------------------------------------------------------------
*******************************************************************************/

//**--------------ͷ�ļ�-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"
#include "stdio.h"
#include "string.h"

#include "userdefine.h"












//**--------------ȫ�ֱ���-----------------------------------------------------

unsigned int system_power_on_time_count=0x00;





//**--------------�궨��-------------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------







/**********************************************************************
*�������ƣ�init_osc
*������ϵͳʱ�ӳ�����   24M
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void init_osc(void)
{
	P_SW2 |= EAXFR;							

	IRC24MCR = 0x80;
	while (!(IRC24MCR & 1)); 
												//ϵͳʱ��Դѡ��
    CKSEL = 0x00;                               //ѡ���ڲ�IRC 24MHz ( Ĭ�� )
    
	 P_SW2 &= ~EAXFR;
												//���Ź���ʼ�� 
	 WDT_CONTR = 0x27;                           //ʹ�ܿ��Ź�,���ʱ��ԼΪ4.2s
}











/**********************************************************************
*�������ƣ�driver_init
*�������������ʼ��
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void driver_init(void)
{
	init_osc();	    	//ϵͳʱ������
		
	init_port();		//IO�˿ڼ�����˿ڳ�ʼ��
	
	init_led();     	//��ʼ��LEDָʾ��
	
	init_beep();		//��ʼ��BEEP������
	
	init_timer0();  	//��ʼ����ʱ��TIMER0
	
	init_uart2();   	//��ʼ��uart2
		
	init_pwm();     	//��ʼ��pwm 38KHz �����ز�Ƶ���ź�
	
	init_lcd();			//��ʼ��LCD  Һ����ʾCOG
	
	init_key();			//��ʼ��key 
	
	init_interrupt();	//��ʼ���ж�
	
	
}




/**********************************************************************
*�������ƣ�middle_init
*�������м���ʼ��
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void middle_init(void)
{
	read_param_eeprom();  //��ȡϵͳ����

}







/**********************************************************************
*�������ƣ�application_init
*������Ӧ�ò��ʼ��
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void application_init(void)
{

	TR0 = 1;	  //������ʱ��  1msʱ����ʱ��
	
	system_run_time=0x01;
	
	system_power_on_time_count=0x00;
	
    
    display_string_8x16(1,1,d);
    display_string_8x16(3,17,a);
    display_string_8x16(5,17,b);
    display_string_8x16(7,76,c);
    
    delay_ms(10);
	
    
}







/*---------------------------------------------------------------------
*�������ƣ�main
*������
*�������ͣ�int
*�����βΣ�void
---------------------------------------------------------------------*/
int main(void) // ������
{
	driver_init(); 		// �������ʼ��
	middle_init(); 		// �м���ʼ��
	application_init(); // Ӧ�ò��ʼ��
	
	
	while(1)
	{
		
		CLRWDT();  //ι��  ���Ź�����16s				
		
		if(handle_scan_key_flag==0x01)
		{
			scan_key_value();
			
			handle_scan_key_flag=0x00;
		}
		
		if((poll_task_flag==0x01)&&(menu_index_q==0x01))   //������ѯ��ȡ��������������
		{
			read_run_data();
						
			poll_task_flag=0x00;  //!!
		}
		
		if(display_lcd_flag==0x01)
		{	
			if(menu_index_q==0x00)	//-----���ġ�Ӣ���л���ʾ									 
			{
				if(yuyan_cnt==0x01)
				{
				   display_string_8x16(7,1,e);	
				}
				else
				{
				   display_string_8x16(7,1,f);
				}
			    
			}
			else if(menu_index_q==0x01)   //����״̬������ʾˢ��
			{
				if(zhuangtai_cnt==1)
				{
					sprintf(buf, "%5.2fV\n", p_v/100);   //��������ѹ
					 			 	
					display_string_8x16(3,80,buf);
					 			 	
					sprintf(buf, "%5.2fV\n", b_v/100);   //��ض˵�ѹ
					 			 	
					display_string_8x16(5,80,buf);
					 			 	
					sprintf(buf, "%5.2fV\n", load_v/100); //����˵�ѹ
					 			 	
					display_string_8x16(7,80,buf);
				}
				else if(zhuangtai_cnt==2)
				{
					sprintf(buf, "%5.2fA\n", charge_I/100);  //������
					 			 	
					display_string_8x16(3,80,buf);
					 			 	
					sprintf(buf, "%5.2fA\n", load_I/100);    //����˸��ص���
					 			 	
					display_string_8x16(5,80,buf);
					 
					if(work_mode==0x01)	//����ģʽ--���ֶ�ģʽ
					{
						sprintf(buf, " %02x H\n", sys_mode);
						
						display_string_8x16(7,80,buf);
						
					}
					else//�Զ�ģʽ
					{
						sprintf(buf, " %02x A\n", sys_mode);       //̫���ܿ���������ģʽ��0-����    1-���    2-�ŵ�
					 			 	
						display_string_8x16(7,80,buf);
						
					}		 	
					
				}
				else if(zhuangtai_cnt==3)
				{
					sprintf(buf, "7.t_ad=%04d\n", charge_current_value);  
					 			 	
					display_string_8x16(3,1,buf);
					 			 	
					sprintf(buf, "8.i_ad=%04d\n", discharge_current_value);  
					 			 	
					display_string_8x16(5,1,buf);
					 			 	
					sprintf(buf, "9.T_ad=%04d\n", temperature_value);      
					 			 	
					display_string_8x16(7,1,buf);
				}
				else //��ʷ��¼ ��ص�ѹ
				{
					sprintf(buf, "BT_%02d_HV->%5.2fV\n",day_index,bt_dy[2*day_index]/100);   
					 			 	
					display_string_8x16(3,1,buf);
					 			 	
					sprintf(buf, "BT_%02d_LV->%5.2fV\n",day_index,bt_dy[2*day_index+1]/100);   
					 			 	
					display_string_8x16(5,1,buf);
				}
			}
			else if(menu_index_q==0x02)  //�豸������ʾˢ��
			{
				if(canshu_cnt==1)
				{
					sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
		 			 	
					display_string_8x16(3,82,buf);
		 			 	
					sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
					 			 	
					display_string_8x16(5,82,buf);
					
					
					 			 	
					sprintf(buf, "%3d%%\n", step_01_load_percent);  //��1�׶� ���ܰٷֱ�
					 			 	
					display_string_8x16(7,82,buf);	
					
					sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
					display_string_8x16(7,114,buf);
				}
				else if(canshu_cnt==2)
				{
					sprintf(buf, "%3d%%\n", step_02_load_percent);  //��2�׶� ���ܰٷֱ�
		 			 	
					display_string_8x16(3,82,buf);
					
					sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
					display_string_8x16(3,114,buf);
					
		 			 	
					sprintf(buf, "%3d%%\n", step_03_load_percent);  //��3�׶� ���ܰٷֱ�
					 			 	
					display_string_8x16(5,82,buf);
					
					sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
					display_string_8x16(5,114,buf);
					
					 			 	
					sprintf(buf, "%3d%%\n", step_04_load_percent);  //��4�׶� ���ܰٷֱ�
					 			 	
					display_string_8x16(7,82,buf);	
					
					sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
					display_string_8x16(7,114,buf);
				}
				else
				{
					sprintf(buf, "%3d%%\n", step_05_load_percent);  //��5�׶� ���ܰٷֱ�
		 			 	
					display_string_8x16(3,82,buf);
					
					sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
					display_string_8x16(3,114,buf);
					
					
		 			 	
					sprintf(buf, "%2d\n", bt_id);  			    //�������
					 			 	
					display_string_8x16(5,82,buf);
					 			 	
					sprintf(buf, "%2dmin\n", light_time);  		//���ʱ��
					 			 	
					display_string_8x16(7,82,buf);
				}
					
			}
			else if(menu_index_q==0x03)
			{
					if(canshu_cnt==1)
					{
						sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
		 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
						 			 	
						display_string_8x16(5,82,buf);
						 			 	
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x03;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						sprintf(buf, "%3d%%\n", step_02_load_percent); 
		 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);   
						 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
						display_string_8x16(5,114,buf);
						
						 			 	
						sprintf(buf, "%3d%%\n", step_04_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x03;//!!!!!!!!!!!!
					}
					else
					{
						sprintf(buf, "%3d%%\n", step_05_load_percent); 
		 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						
						
						sprintf(buf, "%2d\n", bt_id);  			    //�������
					 			 	
						display_string_8x16(5,82,buf);
						 			 	
						sprintf(buf, "%2dmin\n", light_time);  		//���ʱ��
						 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=0x03;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==0x05)
			{
					if(canshu_cnt==1)
					{
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
					 			 	
						display_string_8x16(5,82,buf);
										
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ					
							
						sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
			 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x05;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent); 
		 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
						display_string_8x16(5,114,buf);
						 			 	
						sprintf(buf, "%3d%%\n", step_04_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x05;//!!!!!!!!!!!!
					}
					else
					{
						sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						
						sprintf(buf, "%2d\n", bt_id);  			    //�������
					 			 	
						display_string_8x16(5,82,buf);
						 			 	
						sprintf(buf, "%2dmin\n", light_time);  		//���ʱ�� 
						 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=0x05;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==0x07)
			{
					if(canshu_cnt==1)
					{
						sprintf(buf, "%3d%%\n", step_01_load_percent);  //����ģʽ ����������ʰٷֱȣ�����ص����½���һ������ʱ����������ģʽ ����޶��ӳ�LED�Ƶĵ���ʱ�䣩
					 			 	
						display_string_8x16(7,82,buf);
						
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
						 			 	
						display_string_8x16(5,82,buf);					 			 	
						
						sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
			 			 	
						display_string_8x16(3,82,buf);
						
						menu_index_q=0x07;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
						display_string_8x16(5,114,buf);
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x07;//!!!!!!!!!!!!
					}
					else
					{
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%2dmin\n", light_time);  		//���ʱ��
					 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=0x07;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==0x09)
			{
					if(canshu_cnt==1)
					{
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_01_load_percent);  //����ģʽ ����������ʰٷֱȣ�����ص����½���һ������ʱ����������ģʽ ����޶��ӳ�LED�Ƶĵ���ʱ�䣩
					 			 	
						display_string_8x16(7,82,buf);
								
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
						 			 	
						display_string_8x16(5,82,buf);					 			 	
						
						sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
			 			 	
						display_string_8x16(3,82,buf);
						
						menu_index_q=0x09;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
						display_string_8x16(5,114,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x09;//!!!!!!!!!!!!
					}
					else
					{
						
						sprintf(buf, "%2dmin\n", light_time);  		//���ʱ��
					 			 	
						display_string_8x16(7,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
												
						
						menu_index_q=0x09;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==11)
			{
					if(canshu_cnt==1)
					{
												
						sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
			 			 	
						display_string_8x16(3,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
					 			 	
						display_string_8x16(7,82,buf);
								
						sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
						 			 	
						display_string_8x16(5,82,buf);					 			 	
																	
						menu_index_q=11;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
						display_string_8x16(5,114,buf);
						
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=11;//!!!!!!!!!!!!
					}
					else
					{
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ					
						 			 	
						sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
												
						sprintf(buf, "%2dmin\n", light_time);  		//���ʱ��
					 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=11;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==13)
			{
					if(canshu_cnt==1)
					{
												
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //���ع��������趨
						 			 	
						display_string_8x16(5,82,buf);	
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
					 			 	
						display_string_8x16(7,82,buf);
								
						sprintf(buf, "%2d\n", step_01_time_limit);      //��1�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						
						sprintf(buf, "%5.2fV\n", light_pv/100);  //��ص�ѹ�趨--����������ҹͨ��������ѹ
			 			 	
						display_string_8x16(3,82,buf);										 			 	
																	
						menu_index_q=13;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //��4�׶� ʱ��
					 			 	
						display_string_8x16(7,114,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //��2�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //��3�׶� ʱ��
					 			 	
						display_string_8x16(5,114,buf);
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
												
						menu_index_q=13;//!!!!!!!!!!!!
					}
					else
					{
						
						sprintf(buf, "%2d\n", step_05_time_limit);      //��5�׶� ʱ��
					 			 	
						display_string_8x16(3,114,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!�л���ʾ	
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);										
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
												
						sprintf(buf, "%2dmin\n", light_time);  		//���ʱ��
					 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=13;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			display_lcd_flag=0x00;
			
		}
				 
             
         if(uart2_receive_flag==TRUE)  //�������ݴ���
             {                				
                handle_uart2_rx_buf();
                
				S2CON&=~S2REN;
				NOP();
				NOP();
				S2CON|=S2REN;
				
	 			rx_frame_kind=0x00;
	 			
                uart2_receive_byte_count=0x00;  //!!!!!!!!!

                uart2_receive_flag=FALSE;       //!!!!!!!!!

             } 
		
		
	}
	
}
