/******************************************************************************
**                           志和兴业有限公司
**
**                           
**
**--------------基本文件信息---------------------------------------------------
** 文   件   名	: main.c
** 当前    版本	: V1.0 
** 描        述 : 遥控器主程序
** 编   译   器 : kei c51
** 硬        件 : ZH-YK-001  STC8A4K60S
**--------------历史版本信息---------------------------------------------------
** 开始创建日期	: 2018-06-13
** 创   建   人	: 蔡维凯
** 版  	     本 : V1.0
** 描　      述 : 

**-----------------------------------------------------------------------------
*******************************************************************************/

//**--------------头文件-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"
#include "stdio.h"
#include "string.h"

#include "userdefine.h"












//**--------------全局变量-----------------------------------------------------

unsigned int system_power_on_time_count=0x00;





//**--------------宏定义-------------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------







/**********************************************************************
*函数名称：init_osc
*描述：系统时钟初配置   24M
*返回类型：void
*输入形参：void
***********************************************************************/
void init_osc(void)
{
	P_SW2 |= EAXFR;							

	IRC24MCR = 0x80;
	while (!(IRC24MCR & 1)); 
												//系统时钟源选择
    CKSEL = 0x00;                               //选择内部IRC 24MHz ( 默认 )
    
	 P_SW2 &= ~EAXFR;
												//看门狗初始化 
	 WDT_CONTR = 0x27;                           //使能看门狗,溢出时间约为4.2s
}











/**********************************************************************
*函数名称：driver_init
*描述：驱动层初始化
*返回类型：void
*输入形参：void
***********************************************************************/
void driver_init(void)
{
	init_osc();	    	//系统时钟配置
		
	init_port();		//IO端口及外设端口初始化
	
	init_led();     	//初始化LED指示灯
	
	init_beep();		//初始化BEEP蜂鸣器
	
	init_timer0();  	//初始化定时器TIMER0
	
	init_uart2();   	//初始化uart2
		
	init_pwm();     	//初始化pwm 38KHz 红外载波频率信号
	
	init_lcd();			//初始化LCD  液晶显示COG
	
	init_key();			//初始化key 
	
	init_interrupt();	//初始化中断
	
	
}




/**********************************************************************
*函数名称：middle_init
*描述：中间层初始化
*返回类型：void
*输入形参：void
***********************************************************************/
void middle_init(void)
{
	read_param_eeprom();  //读取系统参数

}







/**********************************************************************
*函数名称：application_init
*描述：应用层初始化
*返回类型：void
*输入形参：void
***********************************************************************/
void application_init(void)
{

	TR0 = 1;	  //开启定时器  1ms时基定时器
	
	system_run_time=0x01;
	
	system_power_on_time_count=0x00;
	
    
    display_string_8x16(1,1,d);
    display_string_8x16(3,17,a);
    display_string_8x16(5,17,b);
    display_string_8x16(7,76,c);
    
    delay_ms(10);
	
    
}







/*---------------------------------------------------------------------
*函数名称：main
*描述：
*返回类型：int
*输入形参：void
---------------------------------------------------------------------*/
int main(void) // 主程序
{
	driver_init(); 		// 驱动层初始化
	middle_init(); 		// 中间层初始化
	application_init(); // 应用层初始化
	
	
	while(1)
	{
		
		CLRWDT();  //喂狗  看门狗周期16s				
		
		if(handle_scan_key_flag==0x01)
		{
			scan_key_value();
			
			handle_scan_key_flag=0x00;
		}
		
		if((poll_task_flag==0x01)&&(menu_index_q==0x01))   //周期轮询读取控制器运行数据
		{
			read_run_data();
						
			poll_task_flag=0x00;  //!!
		}
		
		if(display_lcd_flag==0x01)
		{	
			if(menu_index_q==0x00)	//-----中文、英文切换显示									 
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
			else if(menu_index_q==0x01)   //运行状态数据显示刷新
			{
				if(zhuangtai_cnt==1)
				{
					sprintf(buf, "%5.2fV\n", p_v/100);   //光伏输入电压
					 			 	
					display_string_8x16(3,80,buf);
					 			 	
					sprintf(buf, "%5.2fV\n", b_v/100);   //电池端电压
					 			 	
					display_string_8x16(5,80,buf);
					 			 	
					sprintf(buf, "%5.2fV\n", load_v/100); //输出端电压
					 			 	
					display_string_8x16(7,80,buf);
				}
				else if(zhuangtai_cnt==2)
				{
					sprintf(buf, "%5.2fA\n", charge_I/100);  //充电电流
					 			 	
					display_string_8x16(3,80,buf);
					 			 	
					sprintf(buf, "%5.2fA\n", load_I/100);    //输出端负载电流
					 			 	
					display_string_8x16(5,80,buf);
					 
					if(work_mode==0x01)	//测试模式--即手动模式
					{
						sprintf(buf, " %02x H\n", sys_mode);
						
						display_string_8x16(7,80,buf);
						
					}
					else//自动模式
					{
						sprintf(buf, " %02x A\n", sys_mode);       //太阳能控制器工作模式：0-待机    1-充电    2-放电
					 			 	
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
				else //历史记录 电池电压
				{
					sprintf(buf, "BT_%02d_HV->%5.2fV\n",day_index,bt_dy[2*day_index]/100);   
					 			 	
					display_string_8x16(3,1,buf);
					 			 	
					sprintf(buf, "BT_%02d_LV->%5.2fV\n",day_index,bt_dy[2*day_index+1]/100);   
					 			 	
					display_string_8x16(5,1,buf);
				}
			}
			else if(menu_index_q==0x02)  //设备参数显示刷新
			{
				if(canshu_cnt==1)
				{
					sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
		 			 	
					display_string_8x16(3,82,buf);
		 			 	
					sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
					 			 	
					display_string_8x16(5,82,buf);
					
					
					 			 	
					sprintf(buf, "%3d%%\n", step_01_load_percent);  //第1阶段 节能百分比
					 			 	
					display_string_8x16(7,82,buf);	
					
					sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
					display_string_8x16(7,114,buf);
				}
				else if(canshu_cnt==2)
				{
					sprintf(buf, "%3d%%\n", step_02_load_percent);  //第2阶段 节能百分比
		 			 	
					display_string_8x16(3,82,buf);
					
					sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
					display_string_8x16(3,114,buf);
					
		 			 	
					sprintf(buf, "%3d%%\n", step_03_load_percent);  //第3阶段 节能百分比
					 			 	
					display_string_8x16(5,82,buf);
					
					sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
					display_string_8x16(5,114,buf);
					
					 			 	
					sprintf(buf, "%3d%%\n", step_04_load_percent);  //第4阶段 节能百分比
					 			 	
					display_string_8x16(7,82,buf);	
					
					sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
					display_string_8x16(7,114,buf);
				}
				else
				{
					sprintf(buf, "%3d%%\n", step_05_load_percent);  //第5阶段 节能百分比
		 			 	
					display_string_8x16(3,82,buf);
					
					sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
					display_string_8x16(3,114,buf);
					
					
		 			 	
					sprintf(buf, "%2d\n", bt_id);  			    //电池类型
					 			 	
					display_string_8x16(5,82,buf);
					 			 	
					sprintf(buf, "%2dmin\n", light_time);  		//光控时间
					 			 	
					display_string_8x16(7,82,buf);
				}
					
			}
			else if(menu_index_q==0x03)
			{
					if(canshu_cnt==1)
					{
						sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
		 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
						 			 	
						display_string_8x16(5,82,buf);
						 			 	
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x03;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						sprintf(buf, "%3d%%\n", step_02_load_percent); 
		 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);   
						 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
						display_string_8x16(5,114,buf);
						
						 			 	
						sprintf(buf, "%3d%%\n", step_04_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x03;//!!!!!!!!!!!!
					}
					else
					{
						sprintf(buf, "%3d%%\n", step_05_load_percent); 
		 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						
						
						sprintf(buf, "%2d\n", bt_id);  			    //电池类型
					 			 	
						display_string_8x16(5,82,buf);
						 			 	
						sprintf(buf, "%2dmin\n", light_time);  		//光控时间
						 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=0x03;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==0x05)
			{
					if(canshu_cnt==1)
					{
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
					 			 	
						display_string_8x16(5,82,buf);
										
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示					
							
						sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
			 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x05;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent); 
		 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
						display_string_8x16(5,114,buf);
						 			 	
						sprintf(buf, "%3d%%\n", step_04_load_percent);  
						 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x05;//!!!!!!!!!!!!
					}
					else
					{
						sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						
						sprintf(buf, "%2d\n", bt_id);  			    //电池类型
					 			 	
						display_string_8x16(5,82,buf);
						 			 	
						sprintf(buf, "%2dmin\n", light_time);  		//光控时间 
						 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=0x05;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==0x07)
			{
					if(canshu_cnt==1)
					{
						sprintf(buf, "%3d%%\n", step_01_load_percent);  //节能模式 负载输出功率百分比（当电池电量下降到一定门限时进入节能输出模式 最大限度延长LED灯的点亮时间）
					 			 	
						display_string_8x16(7,82,buf);
						
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
						 			 	
						display_string_8x16(5,82,buf);					 			 	
						
						sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
			 			 	
						display_string_8x16(3,82,buf);
						
						menu_index_q=0x07;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
						display_string_8x16(5,114,buf);
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x07;//!!!!!!!!!!!!
					}
					else
					{
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%2dmin\n", light_time);  		//光控时间
					 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=0x07;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==0x09)
			{
					if(canshu_cnt==1)
					{
						
						sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_01_load_percent);  //节能模式 负载输出功率百分比（当电池电量下降到一定门限时进入节能输出模式 最大限度延长LED灯的点亮时间）
					 			 	
						display_string_8x16(7,82,buf);
								
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
						 			 	
						display_string_8x16(5,82,buf);					 			 	
						
						sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
			 			 	
						display_string_8x16(3,82,buf);
						
						menu_index_q=0x09;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
						display_string_8x16(5,114,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=0x09;//!!!!!!!!!!!!
					}
					else
					{
						
						sprintf(buf, "%2dmin\n", light_time);  		//光控时间
					 			 	
						display_string_8x16(7,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
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
												
						sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
			 			 	
						display_string_8x16(3,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
					 			 	
						display_string_8x16(7,82,buf);
								
						sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
						 			 	
						display_string_8x16(5,82,buf);					 			 	
																	
						menu_index_q=11;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
						display_string_8x16(5,114,buf);
						
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						menu_index_q=11;//!!!!!!!!!!!!
					}
					else
					{
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示					
						 			 	
						sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
												
						sprintf(buf, "%2dmin\n", light_time);  		//光控时间
					 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=11;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			else if(menu_index_q==13)
			{
					if(canshu_cnt==1)
					{
												
						sprintf(buf, "%5.2fA\n", load_cc_I/100);  //负载工作电流设定
						 			 	
						display_string_8x16(5,82,buf);	
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_01_load_percent);  
					 			 	
						display_string_8x16(7,82,buf);
								
						sprintf(buf, "%2d\n", step_01_time_limit);      //第1阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						
						sprintf(buf, "%5.2fV\n", light_pv/100);  //光控电压设定--鉴别白天与黑夜通过光伏板电压
			 			 	
						display_string_8x16(3,82,buf);										 			 	
																	
						menu_index_q=13;//!!!!!!!!!!!!	
					}
					else if(canshu_cnt==2)
					{
						
						sprintf(buf, "%2d\n", step_04_time_limit);      //第4阶段 时长
					 			 	
						display_string_8x16(7,114,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示
						
						sprintf(buf, "%3d%%\n", step_02_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);
						 			 	
						sprintf(buf, "%2d\n", step_02_time_limit);      //第2阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						
						sprintf(buf, "%3d%%\n", step_03_load_percent);  
						 			 	
						display_string_8x16(5,82,buf);
						
						sprintf(buf, "%2d\n", step_03_time_limit);      //第3阶段 时长
					 			 	
						display_string_8x16(5,114,buf);
						
						sprintf(buf, "%3d%%\n", step_04_load_percent); 
		 			 	
						display_string_8x16(7,82,buf);
												
						menu_index_q=13;//!!!!!!!!!!!!
					}
					else
					{
						
						sprintf(buf, "%2d\n", step_05_time_limit);      //第5阶段 时长
					 			 	
						display_string_8x16(3,114,buf);
						//---------------------------------
						menu_index_q=0x02;//!!!!!!!!!!!切换显示	
						
						sprintf(buf, "%3d%%\n", step_05_load_percent);   
						 			 	
						display_string_8x16(3,82,buf);										
						
						sprintf(buf, "%2d\n", bt_id);  
						 			 	
						display_string_8x16(5,82,buf);
												
						sprintf(buf, "%2dmin\n", light_time);  		//光控时间
					 			 	
						display_string_8x16(7,82,buf);
						
						menu_index_q=13;//!!!!!!!!!!!!
					}
					
					
					//---------------------------------
			}
			display_lcd_flag=0x00;
			
		}
				 
             
         if(uart2_receive_flag==TRUE)  //红外数据处理
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
