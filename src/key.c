  
//**--------------头文件-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------全局变量-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------


KEY_STATE_NU  KEY_STATE =KEY_UP;

KEY_VALUE_NU  KEY_VALUE =KNOP;


unsigned char scan_key_time_count=0x00;

unsigned char handle_scan_key_flag=0x00;

unsigned char menu_index_q=0x00;

unsigned char zhuangtai_cnt=0x00;

unsigned char canshu_cnt = 0x00;

unsigned char key1_time_count=0x00;

unsigned char canshu_1_weizhi=0x00;

unsigned char canshu_2_weizhi=0x00;

unsigned char canshu_3_weizhi=0x00;

unsigned char canshu_4_weizhi=0x00;

unsigned char canshu_5_weizhi=0x00;

unsigned char canshu_6_weizhi=0x00;

unsigned char canshu_7_weizhi=0x00;

unsigned char canshu_8_weizhi=0x00;

unsigned char canshu_9_weizhi=0x00;

unsigned char canshu_10_weizhi=0x00;

unsigned char canshu_11_weizhi=0x00;

unsigned char canshu_12_weizhi=0x00;

unsigned char canshu_13_weizhi=0x00;

unsigned char canshu_14_weizhi=0x00;

unsigned char poll_time_enable=0x00;

unsigned char poll_task_flag=0x00;

unsigned int poll_time_count=0x00;

unsigned char set_status=0x00;

unsigned int work_mode=0x00;

unsigned int day_index=0x00;

bit    key1_status = 1;

bit    key2_status = 1;

bit    key3_status = 1;

bit    key4_status = 1;

bit    key5_status = 1;

bit    key6_status = 1;

bit    key7_status = 1;

bit    key8_status = 1;

bit    key9_status = 1;

bit    key10_status = 1;

bit    key11_status = 1;

bit    key12_status = 1;


/**********************************************************************
*函数名称：init_key
*描述：初始化按键KEY端口  设置为输入模式
*返回类型：void
*输入形参：void
***********************************************************************/
void init_key(void)
{
  	set_io_mode(PORT2,5,Z_IN);   //K1
	set_io_mode(PORT2,4,Z_IN);   //K2
 	set_io_mode(PORT2,3,Z_IN);   //K3
  	set_io_mode(PORT2,2,Z_IN);   //K4
  	set_io_mode(PORT2,1,Z_IN);   //K5
	set_io_mode(PORT4,2,Z_IN);   //K6 
  	set_io_mode(PORT2,0,Z_IN);   //K7 
  	set_io_mode(PORT4,1,Z_IN);   //K8 
   	set_io_mode(PORT3,7,Z_IN);   //K9 
   	set_io_mode(PORT3,6,Z_IN);   //K10
   	set_io_mode(PORT5,1,Z_IN);   //K11 
   	set_io_mode(PORT5,0,Z_IN);   //K12

}

/**********************************************************************
*函数名称：scan_key_value
*描述：扫描按键状态
*返回类型：void
*输入形参：void
***********************************************************************/
void scan_key_value(void)
{
	unsigned int key_temp;
	
	key_temp=0x00;
	
	key_temp=(key_temp<<1)|K1_GET;
	
	key_temp=(key_temp<<1)|K2_GET;
	
	key_temp=(key_temp<<1)|K3_GET;
	
	key_temp=(key_temp<<1)|K4_GET;
	
	key_temp=(key_temp<<1)|K5_GET;
	
	key_temp=(key_temp<<1)|K6_GET;
	
	key_temp=(key_temp<<1)|K7_GET;
	
	key_temp=(key_temp<<1)|K8_GET;
	
	key_temp=(key_temp<<1)|K9_GET;
	
	key_temp=(key_temp<<1)|K10_GET;
	
	key_temp=(key_temp<<1)|K11_GET;
	
	key_temp=(key_temp<<1)|K12_GET;
	
	switch(key_temp)
	  {
	     case 0x0000: KEY_STATE =KEY_UP;break;
	     
	     case 0x0800: KEY_VALUE =K1;KEY_STATE =KEY_DOWN;break;  //K1 按键   “设置”--“开关”
	
	     case 0x0400: KEY_VALUE =K2;KEY_STATE =KEY_DOWN;break;  //K2 按键   “+”
	 
	     case 0x0200: KEY_VALUE =K3;KEY_STATE =KEY_DOWN;break;  //K3 按键	“-”
	
	     case 0x0100: KEY_VALUE =K4;KEY_STATE =KEY_DOWN;break;  //K4 按键	“状态”
	
	     case 0x0080: KEY_VALUE =K5;KEY_STATE =KEY_DOWN;break;  //K5 按键	“参数”
	 
	     case 0x0040: KEY_VALUE =K6;KEY_STATE =KEY_DOWN;break;  //K6 按键	“保存”
	
	     case 0x0020: KEY_VALUE =K7;KEY_STATE =KEY_DOWN;break;  //K7 按键	“监测”
	   
	     case 0x0010: KEY_VALUE =K8;KEY_STATE =KEY_DOWN;break;  //K8 按键	“设置”
	 
	     case 0x0008: KEY_VALUE =K9;KEY_STATE =KEY_DOWN;break;  //K9 按键	“背光”
	
	     case 0x0004: KEY_VALUE =K10;KEY_STATE =KEY_DOWN;break; //K10 按键	“模式”
	     
	     case 0x0002: KEY_VALUE =K11;KEY_STATE =KEY_DOWN;break; //K11 按键	“充电”
	
	     case 0x0001: KEY_VALUE =K12;KEY_STATE =KEY_DOWN;break; //K12 按键	“放电”
	
	     default:  KEY_STATE =KEY_DOWN;break;
	    
	  }
	  
	  	  
	  if(KEY_STATE==KEY_UP)    //按键上升沿有效
	    {
	      if(KEY_VALUE!=KNOP)  //释放按键
	       {
		         switch(KEY_VALUE)
		         {
				 	case K1:
							 //--------主菜单界面 menu

							poll_time_enable=0x00;
		         					 
		         			poll_time_count=0x00;
								
							poll_task_flag=0x00;

							yuyan_cnt=yuyan_cnt+1;

							yuyan_cnt=yuyan_cnt%2;


							if(menu_index_q==0x01)
							{
								 clear_screen();
		         				 display_run_data();
							}
							else if(menu_index_q>=0x02)
							{
								clear_screen();
						 		display_canshu();
							}

							break;
		         	case K9:LCD_LED_TOG; break;//LCD背光控制
		         	
		         	case K10:				  //模式：自动模式、手动模式			         			
		         			work_mode^=0x01; 
		         			
		         			menu_index_q=0x01;  
		         			
		         			poll_time_enable=0x00; 
							     
							poll_time_count=0x00;
								
							poll_task_flag=0x00;
							
							zhuangtai_cnt = 0x02;
							
										         			
		         			if(work_mode==0x00)
		         			{
		         												
		         				tx_frame_kind=0x06;
			         			
		         				uart2_tx_buf[0]=0x55;
						         
								uart2_tx_buf[1]=0xA6;
													         
								crc_data=crc16(&uart2_tx_buf[1],1);
													         
								uart2_tx_buf[2]=crc_data/256;
													         
								uart2_tx_buf[3]=crc_data%256;
													         
								uart2_tx_buf[4]=0xAA;
													         
								uart2_send_nbyte(uart2_tx_buf,5);
								
							
		         			}	
		         				clear_screen();
		         				display_run_data();
		         				
		         			break;
		         	
		         	
		         	case K11:	//-------手动充电模式	         					
		         			if(work_mode==0x01)
		         			{
			         			menu_index_q=0x01;   
			         			
			         			poll_time_enable=0x00;
							     
							    poll_time_count=0x00;
								
								poll_task_flag=0x00;								
								
			         			tx_frame_kind=0x04;
			         			
		         				uart2_tx_buf[0]=0x55;
						         
								uart2_tx_buf[1]=0xA4;
													         
								crc_data=crc16(&uart2_tx_buf[1],1);
													         
								uart2_tx_buf[2]=crc_data/256;
													         
								uart2_tx_buf[3]=crc_data%256;
													         
								uart2_tx_buf[4]=0xAA;
													         
								uart2_send_nbyte(uart2_tx_buf,5);
								
								clear_screen();
		         				display_run_data();
		         			}	
		         			break;//充电
		         	
		         	case K12:	//-------手动放电模式
		         			
		         			if(work_mode==0x01)
		         			{
			         			menu_index_q=0x01;   
			         			
			         			poll_time_enable=0x00;
							     
							    poll_time_count=0x00;
								
								poll_task_flag=0x00;
																			         			
			         			tx_frame_kind=0x05;
			         			
		         				uart2_tx_buf[0]=0x55;
						         
								uart2_tx_buf[1]=0xA5;
													         
								crc_data=crc16(&uart2_tx_buf[1],1);
													         
								uart2_tx_buf[2]=crc_data/256;
													         
								uart2_tx_buf[3]=crc_data%256;
													         
								uart2_tx_buf[4]=0xAA;
													         
								uart2_send_nbyte(uart2_tx_buf,5);
								
								clear_screen();
		         				display_run_data();
		         			}
		         			break;//放电
		         	
		         	case K7:                    //轮询读取控制器运行数据
		         			menu_index_q	= 0x01; 
		         			
		         			poll_time_enable= 0x01;
		         			
		         			//zhuangtai_cnt	= 0x01;		   //---caiwk-2018-6-20
		         			
		         			//--------------------------------------------
		         			clear_screen();
		         			display_run_data();
		         			//-------------------------------------------
		         			break;
		         	
		         	case K6:  //---------------------------------------------------参数保存  发送参数到控制器
		         			{
		         					 menu_index_q=0x02;		
		         					 
		         					 poll_time_enable=0x00;
		         					 
		         					 poll_time_count=0x00;
								
								 	 poll_task_flag=0x00;
								 	 
								 	 
								 	 //canshu_cnt = 1;
								 	 //--------------------------------------------
								 	 
								 	 save_sys_parameter();
						 			 
						 			 //-----------------------------------------------
						 			 clear_screen();
						 			 display_canshu();
						 			 //----------------------------------------------
		         			}
		         			
		         			break;
		         	
		         	case K4:  		//-----------------------------------------------读取控制器"运行数据"
			         		{
							     menu_index_q=0x01;   
							     
							     poll_time_count=0x00;
								
								 poll_task_flag=0x00;
								 
								 //--------------------------------------------
								
								 read_run_data();
					 			 
					 			 //--------------------------------------------
					 			 
					 			 zhuangtai_cnt = zhuangtai_cnt+1;
					 			 
					 			 zhuangtai_cnt = zhuangtai_cnt%4;
					 			 
					 			 clear_screen();
		         				 display_run_data();
					 			 
					 		}
					 		
					 		break;
					 		
					 case K5:	//------------------------------------------------读取控制器"系统参数"
					 		{
						 			 menu_index_q=0x02;		
						 			 
						 			 poll_time_enable=0x00;
		         					 
		         					 poll_time_count=0x00;
								
								 	 poll_task_flag=0x00;
								 	 
								 	 //--------------------------------------
								 	 
								 	 read_sys_parameter();
						 			 
						 			 //----------------------------------------
						 			 
						 			 canshu_cnt = canshu_cnt+1;
						 			 
						 			 canshu_cnt = canshu_cnt%3;
						 			 
						 			 //--------------------------------------显示参数界面
						 			 
						 			 clear_screen();
						 			 display_canshu();
						 			 
						 			 
						 			 
					 		}
					 		
					 		break;
					 		
					 case K8:  								 //按键	"设置"
					 			if(menu_index_q==0x02)
					 			{
						 				menu_index_q=0x03;       //所要修改数字位置跳变
						 				
						 				if(canshu_cnt==1)
						 				{
						 					canshu_1_weizhi=0x00;
						 				}
						 				else if(canshu_cnt==2)
						 				{
						 					canshu_5_weizhi=0x00;
						 				}
						 				else
						 				{
						 					canshu_11_weizhi=0x00;
						 				}
					 				
					 				
					 			}
					 			else if(menu_index_q==0x03)
					 			{
					 									 				
						 				if(canshu_cnt==1)
						 				{
						 					canshu_1_weizhi++;
						 					
						 					if(light_pv>=1000)
							 				{
							 					canshu_1_weizhi=canshu_1_weizhi%4;
							 				}
							 				else
							 				{
							 					canshu_1_weizhi=canshu_1_weizhi%3;
							 				}
						 				}
						 				else if(canshu_cnt==2)
						 				{
						 					canshu_5_weizhi++;
						 											 					
							 				if(step_02_load_percent>=10)
							 				{
							 					canshu_5_weizhi=canshu_5_weizhi%2;
							 				}
							 				else
							 				{
							 					canshu_5_weizhi=canshu_5_weizhi%1;
							 				}
						 					
						 				}
						 				else
						 				{
						 					canshu_11_weizhi++;
						 					
						 					if(step_05_load_percent>=10)
							 				{
							 					canshu_11_weizhi=canshu_11_weizhi%2;
							 				}
							 				else
							 				{
							 					canshu_11_weizhi=canshu_11_weizhi%1;
							 				}
						 				}
						 									 				
					 				
					 			}
					 			else if(menu_index_q==0x04)
					 			{
							 				menu_index_q=0x05;      //所要修改数字位置跳变
							 				
							 				if(canshu_cnt==1)
							 				{
							 					canshu_2_weizhi=0x00;
							 				}
							 				else if(canshu_cnt==2)
							 				{
							 					canshu_6_weizhi=0x00;
							 				}
							 				else
							 				{
							 					canshu_12_weizhi=0x00;
							 				}
					 			}
					 			else if(menu_index_q==0x05)
					 			{
						 				if(canshu_cnt==1)
						 				{
						 					canshu_2_weizhi++;
						 					
						 					if(load_cc_I>=1000)
							 				{
							 					canshu_2_weizhi=canshu_2_weizhi%4;
							 				}
							 				else
							 				{
							 					canshu_2_weizhi=canshu_2_weizhi%3;
							 				}
						 				}
						 				else if(canshu_cnt==2)
						 				{
						 					canshu_6_weizhi++;
						 					
						 					if(step_02_time_limit>=10)
							 				{
							 					canshu_6_weizhi=canshu_6_weizhi%2;
							 				}
							 				else
							 				{
							 					canshu_6_weizhi=canshu_6_weizhi%1;
							 				}
						 				}
						 				else
						 				{
						 					canshu_12_weizhi++;
						 					
						 					if(step_05_time_limit>=10)
							 				{
							 					canshu_12_weizhi=canshu_12_weizhi%2;
							 				}
							 				else
							 				{
							 					canshu_12_weizhi=canshu_12_weizhi%1;
							 				}
						 				}
						 				
						 				
					 			}
					 			else if(menu_index_q==0x06)
					 			{
					 				menu_index_q=0x07;      //所要修改数字位置跳变
					 				
					 				if(canshu_cnt==1)
							 		{
							 			canshu_3_weizhi=0x00;
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_7_weizhi=0x00;
							 		}
							 		else
							 		{
							 			canshu_13_weizhi=0x00;
							 		}
					 			}
					 			else if(menu_index_q==0x07)
					 			{
					 				if(canshu_cnt==1)
							 		{
							 			canshu_3_weizhi++;
							 			
							 			if(step_01_load_percent>=10)
						 				{
						 					canshu_3_weizhi=canshu_3_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_3_weizhi=canshu_3_weizhi%1;
						 				}
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_7_weizhi++;
							 			
							 			if(step_03_load_percent>=10)
						 				{
						 					canshu_7_weizhi=canshu_7_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_7_weizhi=canshu_7_weizhi%1;
						 				}
							 		}
							 		else
							 		{
							 			canshu_13_weizhi++;
							 			
							 			if(bt_id>=10)
						 				{
						 					canshu_13_weizhi=canshu_13_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_13_weizhi=canshu_13_weizhi%1;
						 				}
							 		}					 									 									 				
					 				
					 			}
					 			else if(menu_index_q==0x08)
					 			{
					 				menu_index_q=0x09;      //所要修改数字位置跳变
					 				
					 				if(canshu_cnt==1)
							 		{
							 			canshu_4_weizhi=0x00;
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_8_weizhi=0x00;
							 		}
							 		else
							 		{
							 			canshu_14_weizhi=0x00;
							 		}
					 			}
					 			else if(menu_index_q==0x09)
					 			{
					 				if(canshu_cnt==1)
							 		{
							 			canshu_4_weizhi++;
							 			
							 			if(step_01_time_limit>=10)
						 				{
						 					canshu_4_weizhi=canshu_4_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_4_weizhi=canshu_4_weizhi%1;
						 				}
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_8_weizhi++;
							 			
							 			if(step_03_time_limit>=10)
						 				{
						 					canshu_8_weizhi=canshu_8_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_8_weizhi=canshu_8_weizhi%1;
						 				}
							 		}
							 		else
							 		{
							 			canshu_14_weizhi++;
							 			
							 			if(light_time>=10)
						 				{
						 					canshu_14_weizhi=canshu_14_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_14_weizhi=canshu_14_weizhi%1;
						 				}
							 		}					 									 									 				
					 				
					 			}
					 			else if(menu_index_q==10)
					 			{
					 				menu_index_q=11;      //所要修改数字位置跳变
					 				
					 				if(canshu_cnt==1)
							 		{
							 			canshu_1_weizhi=0x00;
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_9_weizhi=0x00;
							 		}
							 		else
							 		{
							 			canshu_11_weizhi=0x00;
							 		}
					 			}
					 			else if(menu_index_q==11)
					 			{
					 				if(canshu_cnt==1)
							 		{
							 			canshu_1_weizhi++;
							 			
							 			if(light_pv>=1000)
						 				{
						 					canshu_1_weizhi=canshu_1_weizhi%4;
						 				}
						 				else
						 				{
						 					canshu_1_weizhi=canshu_1_weizhi%3;
						 				}
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_9_weizhi++;
							 			
							 			if(step_04_load_percent>=10)
						 				{
						 					canshu_9_weizhi=canshu_9_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_9_weizhi=canshu_9_weizhi%1;
						 				}
							 		}
							 		else
							 		{
							 			canshu_11_weizhi++;
							 			
							 			if(step_05_load_percent>=10)
						 				{
						 					canshu_11_weizhi=canshu_11_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_11_weizhi=canshu_11_weizhi%1;
						 				}
							 		}					 									 									 				
					 				
					 			}
					 			else if(menu_index_q==12)
					 			{
					 				menu_index_q=13;      //所要修改数字位置跳变
					 				
					 				if(canshu_cnt==1)
							 		{
							 			canshu_2_weizhi=0x00;
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_10_weizhi=0x00;
							 		}
							 		else
							 		{
							 			canshu_12_weizhi=0x00;
							 		}
					 			}
					 			else if(menu_index_q==13)
					 			{
					 				if(canshu_cnt==1)
							 		{
							 			canshu_2_weizhi++;
							 			
							 			if(load_cc_I>=1000)
						 				{
						 					canshu_2_weizhi=canshu_2_weizhi%4;
						 				}
						 				else
						 				{
						 					canshu_2_weizhi=canshu_2_weizhi%3;
						 				}
							 		}
							 		else if(canshu_cnt==2)
							 		{
							 			canshu_10_weizhi++;
							 			
							 			if(step_04_time_limit>=10)
						 				{
						 					canshu_10_weizhi=canshu_10_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_10_weizhi=canshu_10_weizhi%1;
						 				}
							 		}
							 		else
							 		{
							 			canshu_12_weizhi++;
							 			
							 			if(step_05_time_limit>=10)
						 				{
						 					canshu_12_weizhi=canshu_12_weizhi%2;
						 				}
						 				else
						 				{
						 					canshu_12_weizhi=canshu_12_weizhi%1;
						 				}
							 		}					 									 									 				
					 				
					 			}
					 		 break;
					 		
					 case K2:   // "+"
					 			
					 			if(menu_index_q==0x01 && zhuangtai_cnt==0x00)
					 			{
					 				day_index = day_index + 1;
					 				
					 				day_index = day_index%8;
					 			}
					 		
					 			if(menu_index_q==0x03)   //参数1设置  光控电压
					 			{
					 					if(canshu_cnt==1)
					 					{
					 							switch(canshu_1_weizhi)
							 					{
							 						case 0:		
							 								if(light_pv<=9998)
							 								{
							 									light_pv = light_pv + 1	;	
							 								}
							 								break;
							 						case 1:		
							 								if(light_pv<=9989)
							 								{
							 									light_pv = light_pv + 10	;	
							 								}
							 								break;	
							 						case 2:		
							 								if(light_pv<=9899)
							 								{
							 									light_pv = light_pv + 100	;	
							 								}
							 								break;
							 						case 3:		
							 								if(light_pv<=8999)
							 								{
							 									light_pv = light_pv + 1000;	
							 								}
							 								break;
							 						default:break;
							 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_5_weizhi)
							 					{
							 						case 0:		
							 								if(step_02_load_percent<=99)
							 								{
							 									step_02_load_percent = step_02_load_percent + 1	;	
							 								}
							 								break;
							 						case 1:		
							 								if(step_02_load_percent<=89)
							 								{
							 									step_02_load_percent = step_02_load_percent + 10	;	
							 								}
							 								break;	
							 						default:break;
							 					}	
					 					}
					 					else
					 					{
					 						switch(canshu_11_weizhi)
							 					{
							 						case 0:		
							 								if(step_05_load_percent<=99)
							 								{
							 									step_05_load_percent = step_05_load_percent + 1	;	
							 								}
							 								break;
							 						case 1:		
							 								if(step_05_load_percent<=89)
							 								{
							 									step_05_load_percent = step_05_load_percent + 10	;	
							 								}
							 								break;	
							 						default:break;
							 					}
					 					}
					 				
				 				
					 			}
					 			else if(menu_index_q==0x05)   //参数2设置  负载电流
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_2_weizhi)
						 					{
						 						case 0:		
						 								if(load_cc_I<=9998)
						 								{
						 									load_cc_I = load_cc_I + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(load_cc_I<=9989)
						 								{
						 									load_cc_I = load_cc_I + 10	;	
						 								}
						 								break;	
						 						case 2:		
						 								if(load_cc_I<=9899)
						 								{
						 									load_cc_I = load_cc_I + 100	;	
						 								}
						 								break;
						 						case 3:		
						 								if(load_cc_I<=8999)
						 								{
						 									load_cc_I = load_cc_I + 1000;	
						 								}
						 								break;
						 						default:break;
						 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_6_weizhi)
						 					{
						 						case 0:		
							 							if(step_02_time_limit<=23)
							 							{
							 								step_02_time_limit = step_02_time_limit + 1	;	
							 							}
							 							break;
							 					case 1:		
							 							if(step_02_time_limit<=13)
							 							{
							 								step_02_time_limit = step_02_time_limit + 10	;	
							 							}
							 							break;
						 	
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_12_weizhi)
						 					{
						 						case 0:		
							 							if(step_05_time_limit<=23)
							 							{
							 								step_05_time_limit = step_05_time_limit + 1	;	
							 							}
							 							break;
							 					case 1:		
							 							if(step_05_time_limit<=13)
							 							{
							 								step_05_time_limit = step_05_time_limit + 10	;	
							 							}
							 							break;
						 	
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==0x07)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_3_weizhi)
						 					{
						 						case 0:		
						 								if(step_01_load_percent<=99)
						 								{
						 									step_01_load_percent = step_01_load_percent + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_01_load_percent<=89)
						 								{
						 									step_01_load_percent = step_01_load_percent + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_7_weizhi)
						 					{
						 						case 0:		
						 								if(step_03_load_percent<=99)
						 								{
						 									step_03_load_percent = step_03_load_percent + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_03_load_percent<=89)
						 								{
						 									step_03_load_percent = step_03_load_percent + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_13_weizhi)
						 					{
						 						case 0:		
						 								if(bt_id<=59)
						 								{
						 									bt_id = bt_id + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(bt_id<=49)
						 								{
						 									bt_id = bt_id + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}	
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==0x09)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_4_weizhi)
						 					{
						 						case 0:		
						 								if(step_01_time_limit<=23)
						 								{
						 									step_01_time_limit = step_01_time_limit + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_01_time_limit<=13)
						 								{
						 									step_01_time_limit = step_01_time_limit + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_8_weizhi)
						 					{
						 						case 0:		
						 								if(step_03_time_limit<=23)
						 								{
						 									step_03_time_limit = step_03_time_limit + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_03_time_limit<=13)
						 								{
						 									step_03_time_limit = step_03_time_limit + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_14_weizhi)
						 					{
						 						case 0:		
						 								if(light_time<=59)
						 								{
						 									light_time = light_time + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(light_time<=49)
						 								{
						 									light_time = light_time + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}	
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==11)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_1_weizhi)
							 					{
							 						case 0:		
							 								if(light_pv<=9998)
							 								{
							 									light_pv = light_pv + 1	;	
							 								}
							 								break;
							 						case 1:		
							 								if(light_pv<=9989)
							 								{
							 									light_pv = light_pv + 10	;	
							 								}
							 								break;	
							 						case 2:		
							 								if(light_pv<=9899)
							 								{
							 									light_pv = light_pv + 100	;	
							 								}
							 								break;
							 						case 3:		
							 								if(light_pv<=8999)
							 								{
							 									light_pv = light_pv + 1000;	
							 								}
							 								break;
							 						default:break;
							 					}
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_9_weizhi)
						 					{
						 						case 0:		
						 								if(step_04_load_percent<=99)
						 								{
						 									step_04_load_percent = step_04_load_percent + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_04_load_percent<=89)
						 								{
						 									step_04_load_percent = step_04_load_percent + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_11_weizhi)
						 					{
						 						case 0:		
						 								if(step_05_load_percent<=99)
						 								{
						 									step_05_load_percent = step_05_load_percent + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_05_load_percent<=89)
						 								{
						 									step_05_load_percent = step_05_load_percent + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}	
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==13)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_2_weizhi)
						 					{
						 						case 0:		
						 								if(load_cc_I<=9998)
						 								{
						 									load_cc_I = load_cc_I + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(load_cc_I<=9989)
						 								{
						 									load_cc_I = load_cc_I + 10	;	
						 								}
						 								break;	
						 						case 2:		
						 								if(load_cc_I<=9899)
						 								{
						 									load_cc_I = load_cc_I + 100	;	
						 								}
						 								break;
						 						case 3:		
						 								if(load_cc_I<=8999)
						 								{
						 									load_cc_I = load_cc_I + 1000;	
						 								}
						 								break;
						 						default:break;
						 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_10_weizhi)
						 					{
						 						case 0:		
						 								if(step_04_time_limit<=23)
						 								{
						 									step_04_time_limit = step_04_time_limit + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_04_time_limit<=13)
						 								{
						 									step_04_time_limit = step_04_time_limit + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_12_weizhi)
						 					{
						 						case 0:		
						 								if(step_05_time_limit<=23)
						 								{
						 									step_05_time_limit = step_05_time_limit + 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_05_time_limit<=13)
						 								{
						 									step_05_time_limit = step_05_time_limit + 10	;	
						 								}
						 								break;	
						 					
						 						default:break;
						 					}	
					 					}
					 					
				 				
					 			}
					 			break;
					 			
					 case K3://"-"
					 			if(menu_index_q==0x01 && zhuangtai_cnt==0x00)
					 			{
						 			if(day_index>0)
						 			{
						 				day_index = day_index - 1;
						 			}					 				
					 				
					 			}
					 			
					 			if(menu_index_q==0x03)   //参数1设置  光控电压
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_1_weizhi)
						 					{
						 						case 0:		
						 								if(light_pv>=1)
						 								{
						 									light_pv = light_pv - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(light_pv>=10)
						 								{
						 									light_pv = light_pv - 10	;
						 									
						 									if(light_pv<10)
						 									{
						 										canshu_1_weizhi=0x00;
						 									}	
						 								}
						 								break;	
						 						case 2:		
						 								if(light_pv>=100)
						 								{
						 									light_pv = light_pv - 100	;
						 									
						 									if(light_pv<100)
						 									{
						 										canshu_1_weizhi=0x01;
						 									}	
						 								}
						 								break;
						 						case 3:		
						 								if(light_pv>=1000)
						 								{
						 									light_pv = light_pv - 1000;	
						 									
						 									if(light_pv<1000)
						 									{
						 										canshu_1_weizhi=0x02;
						 									}
						 								}
						 								break;
						 						default:break;
						 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_5_weizhi)
						 					{
						 						case 0:		
						 								if(step_02_load_percent>=1)
						 								{
						 									step_02_load_percent = step_02_load_percent - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_02_load_percent>=10)
						 								{
						 									step_02_load_percent = step_02_load_percent - 10	;
						 									
						 									if(step_02_load_percent<10)
						 									{
						 										canshu_5_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_11_weizhi)
						 					{
						 						case 0:		
						 								if(step_05_load_percent>=1)
						 								{
						 									step_05_load_percent = step_05_load_percent - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_05_load_percent>=10)
						 								{
						 									step_05_load_percent = step_05_load_percent - 10	;
						 									
						 									if(step_05_load_percent<10)
						 									{
						 										canshu_11_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==0x05)   //参数2设置  负载电流
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_2_weizhi)
						 					{
						 						case 0:		
						 								if(load_cc_I>=1)
						 								{
						 									load_cc_I = load_cc_I - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(load_cc_I>=10)
						 								{
						 									load_cc_I = load_cc_I - 10	;
						 									
						 									if(load_cc_I<10)
						 									{
						 										canshu_2_weizhi=0x00;
						 									}	
						 								}
						 								break;	
						 						case 2:		
						 								if(load_cc_I>=100)
						 								{
						 									load_cc_I = load_cc_I - 100	;
						 									
						 									if(load_cc_I<100)
						 									{
						 										canshu_2_weizhi=0x01;
						 									}	
						 								}
						 								break;
						 						case 3:		
						 								if(load_cc_I>=1000)
						 								{
						 									load_cc_I = load_cc_I - 1000;	
						 									
						 									if(load_cc_I<1000)
						 									{
						 										canshu_2_weizhi=0x02;
						 									}
						 								}
						 								break;
						 						default:break;
						 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_6_weizhi)
						 					{
						 						case 0:		
						 								if(step_02_time_limit>=1)
						 								{
						 									step_02_time_limit = step_02_time_limit - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_02_time_limit>=10)
						 								{
						 									step_02_time_limit = step_02_time_limit - 10	;
						 									
						 									if(step_02_time_limit<10)
						 									{
						 										canshu_6_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_12_weizhi)
						 					{
						 						case 0:		
						 								if(step_05_time_limit>=1)
						 								{
						 									step_05_time_limit = step_05_time_limit - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_05_time_limit>=10)
						 								{
						 									step_05_time_limit = step_05_time_limit - 10	;
						 									
						 									if(step_05_time_limit<10)
						 									{
						 										canshu_12_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==0x07)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_3_weizhi)
						 					{
						 						case 0:		
						 								if(step_01_load_percent>=1)
						 								{
						 									step_01_load_percent = step_01_load_percent - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_01_load_percent>=10)
						 								{
						 									step_01_load_percent = step_01_load_percent - 10	;
						 									
						 									if(step_01_load_percent<10)
						 									{
						 										canshu_3_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_7_weizhi)
						 					{
						 						case 0:		
						 								if(step_03_load_percent>=1)
						 								{
						 									step_03_load_percent = step_03_load_percent - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_03_load_percent>=10)
						 								{
						 									step_03_load_percent = step_03_load_percent - 10	;
						 									
						 									if(step_03_load_percent<10)
						 									{
						 										canshu_7_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_13_weizhi)
						 					{
						 						case 0:		
						 								if(bt_id>=1)
						 								{
						 									bt_id = bt_id - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(bt_id>=10)
						 								{
						 									bt_id = bt_id - 10	;
						 									
						 									if(bt_id<10)
						 									{
						 										canshu_13_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==0x09)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_4_weizhi)
						 					{
						 						case 0:		
						 								if(step_01_time_limit>=1)
						 								{
						 									step_01_time_limit = step_01_time_limit - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_01_time_limit>=10)
						 								{
						 									step_01_time_limit = step_01_time_limit - 10	;
						 									
						 									if(step_01_time_limit<10)
						 									{
						 										canshu_4_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_8_weizhi)
						 					{
						 						case 0:		
						 								if(step_03_time_limit>=1)
						 								{
						 									step_03_time_limit = step_03_time_limit - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_03_time_limit>=10)
						 								{
						 									step_03_time_limit = step_03_time_limit - 10	;
						 									
						 									if(step_03_time_limit<10)
						 									{
						 										canshu_8_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_14_weizhi)
						 					{
						 						case 0:		
						 								if(light_time>=1)
						 								{
						 									light_time = light_time - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(light_time>=10)
						 								{
						 									light_time = light_time - 10	;
						 									
						 									if(light_time<10)
						 									{
						 										canshu_14_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==11)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_1_weizhi)
						 					{
						 						case 0:		
						 								if(light_pv>=1)
						 								{
						 									light_pv = light_pv - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(light_pv>=10)
						 								{
						 									light_pv = light_pv - 10	;
						 									
						 									if(light_pv<10)
						 									{
						 										canshu_1_weizhi=0x00;
						 									}	
						 								}
						 								break;	
						 						case 2:		
						 								if(light_pv>=100)
						 								{
						 									light_pv = light_pv - 100	;
						 									
						 									if(light_pv<100)
						 									{
						 										canshu_1_weizhi=0x01;
						 									}	
						 								}
						 								break;
						 						case 3:		
						 								if(light_pv>=1000)
						 								{
						 									light_pv = light_pv - 1000;	
						 									
						 									if(light_pv<1000)
						 									{
						 										canshu_1_weizhi=0x02;
						 									}
						 								}
						 								break;
						 						default:break;
						 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_9_weizhi)
						 					{
						 						case 0:		
						 								if(step_04_load_percent>=1)
						 								{
						 									step_04_load_percent = step_04_load_percent - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_04_load_percent>=10)
						 								{
						 									step_04_load_percent = step_04_load_percent - 10	;
						 									
						 									if(step_04_load_percent<10)
						 									{
						 										canshu_9_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_11_weizhi)
						 					{
						 						case 0:		
						 								if(step_05_load_percent>=1)
						 								{
						 									step_05_load_percent = step_05_load_percent - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_05_load_percent>=10)
						 								{
						 									step_05_load_percent = step_05_load_percent - 10	;
						 									
						 									if(step_05_load_percent<10)
						 									{
						 										canshu_11_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			else if(menu_index_q==13)   //参数3设置  节能输出百分比
					 			{
					 					if(canshu_cnt==1)
					 					{
					 						switch(canshu_2_weizhi)
						 					{
						 						case 0:		
						 								if(load_cc_I>=1)
						 								{
						 									load_cc_I = load_cc_I - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(load_cc_I>=10)
						 								{
						 									load_cc_I = load_cc_I - 10	;
						 									
						 									if(load_cc_I<10)
						 									{
						 										canshu_2_weizhi=0x00;
						 									}	
						 								}
						 								break;	
						 						case 2:		
						 								if(load_cc_I>=100)
						 								{
						 									load_cc_I = load_cc_I - 100	;
						 									
						 									if(load_cc_I<100)
						 									{
						 										canshu_2_weizhi=0x01;
						 									}	
						 								}
						 								break;
						 						case 3:		
						 								if(load_cc_I>=1000)
						 								{
						 									load_cc_I = load_cc_I - 1000;	
						 									
						 									if(load_cc_I<1000)
						 									{
						 										canshu_2_weizhi=0x02;
						 									}
						 								}
						 								break;
						 						default:break;
						 					}	
					 					}
					 					else if(canshu_cnt==2)
					 					{
					 						switch(canshu_10_weizhi)
						 					{
						 						case 0:		
						 								if(step_04_time_limit>=1)
						 								{
						 									step_04_time_limit = step_04_time_limit - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_04_time_limit>=10)
						 								{
						 									step_04_time_limit = step_04_time_limit - 10	;
						 									
						 									if(step_04_time_limit<10)
						 									{
						 										canshu_10_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					else
					 					{
					 						switch(canshu_12_weizhi)
						 					{
						 						case 0:		
						 								if(step_05_time_limit>=1)
						 								{
						 									step_05_time_limit = step_05_time_limit - 1	;	
						 								}
						 								break;
						 						case 1:		
						 								if(step_05_time_limit>=10)
						 								{
						 									step_05_time_limit = step_05_time_limit - 10	;
						 									
						 									if(step_05_time_limit<10)
						 									{
						 										canshu_12_weizhi=0x00;
						 									}
						 								}
						 								break;	
						 					
						 						default:break;
						 					}
					 					}
					 					
				 				
					 			}
					 			break;
					 
					 default:break;
					 		
		         }
		        

	         KEY_VALUE=KNOP;
	         
	         system_power_on_time_count=0x00;  //每次有效按键清除开机变量数值
	
	         BEEP_SPEAK();
	         
	       }
	
	    }
	    
	    
	    if(menu_index_q==0x03)
		  {
		  		if((KEY_VALUE ==K8)&&(KEY_STATE == KEY_DOWN))     //	长按“设置”键
		  		{
		  			if(key1_time_count<15)
					{
					  key1_time_count++;
							
					}
					else
					{
						key1_time_count=0x00;
						
						if(canshu_cnt==1)
					 	{
					 		canshu_1_weizhi=0x00;
					 	}
					 	else if(canshu_cnt==2)
					 	{
					 		canshu_5_weizhi=0x00;
					 	}
					 	else
					 	{
					 		canshu_11_weizhi=0x00;
					 	}
						
						menu_index_q=0x04;
						
						BEEP_SPEAK();
					}
		  		}
		  		else
		  		{
		  				key1_time_count=0x00;
	
					
		  		}
		  }
		  else if(menu_index_q==0x05)
		  {
		  		if((KEY_VALUE ==K8)&&(KEY_STATE == KEY_DOWN))
		  		{
		  			if(key1_time_count<15)
					{
					  key1_time_count++;
							
					}
					else
					{
						key1_time_count=0x00;
						
						if(canshu_cnt==1)
					 	{
					 		canshu_2_weizhi=0x00;
					 	}
					 	else if(canshu_cnt==2)
					 	{
					 		canshu_6_weizhi=0x00;
					 	}
					 	else
					 	{
					 		canshu_12_weizhi=0x00;
					 	}
						
						menu_index_q=0x06;
						
						BEEP_SPEAK();
					}
		  		}
		  		else
		  		{
		  				key1_time_count=0x00;
	
						
		  		}
		  }
		  else if(menu_index_q==0x07)
		  {
		  		if((KEY_VALUE ==K8)&&(KEY_STATE == KEY_DOWN))
		  		{
		  			if(key1_time_count<15)
					{
					  key1_time_count++;
							
					}
					else
					{
						key1_time_count=0x00;
						
						if(canshu_cnt==1)
						{
							 canshu_3_weizhi=0x00;
						}
						else if(canshu_cnt==2)
						{
							 canshu_7_weizhi=0x00;
						}
						else
						{
							 canshu_13_weizhi=0x00;
						}
						
						menu_index_q=0x08;
						
						BEEP_SPEAK();
					}
		  		}
		  		else
		  		{
		  				key1_time_count=0x00;
	
						
		  		}
		  }
		  else if(menu_index_q==0x09)
		  {
		  		if((KEY_VALUE ==K8)&&(KEY_STATE == KEY_DOWN))
		  		{
		  			if(key1_time_count<15)
					{
					  key1_time_count++;
							
					}
					else
					{
						key1_time_count=0x00;
						
						if(canshu_cnt==1)
						{
							 canshu_4_weizhi=0x00;
						}
						else if(canshu_cnt==2)
						{
							 canshu_8_weizhi=0x00;
						}
						else
						{
							 canshu_14_weizhi=0x00;
						}
						
						menu_index_q=10;
						
						BEEP_SPEAK();
					}
		  		}
		  		else
		  		{
		  				key1_time_count=0x00;
	
						
		  		}
		  }
		  else if(menu_index_q==11)
		  {
		  		if((KEY_VALUE ==K8)&&(KEY_STATE == KEY_DOWN))
		  		{
		  			if(key1_time_count<15)
					{
					  key1_time_count++;
							
					}
					else
					{
						key1_time_count=0x00;
						
						if(canshu_cnt==1)
						{
							 canshu_1_weizhi=0x00;
						}
						else if(canshu_cnt==2)
						{
							 canshu_9_weizhi=0x00;
						}
						else
						{
							 canshu_11_weizhi=0x00;
						}
						
						menu_index_q=12;
						
						BEEP_SPEAK();
					}
		  		}
		  		else
		  		{
		  				key1_time_count=0x00;
	
						
		  		}
		  }
		  else if(menu_index_q==13)
		  {
		  		if((KEY_VALUE ==K8)&&(KEY_STATE == KEY_DOWN))
		  		{
		  			if(key1_time_count<15)
					{
					  key1_time_count++;
							
					}
					else
					{
						key1_time_count=0x00;
						
						if(canshu_cnt==1)
						{
							 canshu_2_weizhi=0x00;
						}
						else if(canshu_cnt==2)
						{
							 canshu_10_weizhi=0x00;
						}
						else
						{
							 canshu_12_weizhi=0x00;
						}
						
						menu_index_q=0x02;
						
						BEEP_SPEAK();
					}
		  		}
		  		else
		  		{
		  				key1_time_count=0x00;
	
						
		  		}
		  }
	
}





