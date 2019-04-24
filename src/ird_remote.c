//**--------------头文件-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------全局变量-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------

//**--------------函数定义-----------------------------------------------------




//系统运行状态数据及设置参数
//------------------------------------------------------------------------------//
//		__EEPROM_DATA(0x02, 0x58, 0x00, 0x21, 0x14, 0x3C, 0x50, 0x3C);
//		
//		__EEPROM_DATA(0x14, 0x01, 0x01, 0x01, 0x01, 0x03, 0x04, 0x03);
//		
//		__EEPROM_DATA(0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
//------------------------------------------------------------------------------//
//-----------------------运行数据
float p_v=0;    						//当前光伏电压

float b_v=0;							//当前电池电压

float load_v=0;							//当前负载电压

float charge_I =0; 						//当前充电电流

float load_I =0;    					//当前负载电流

unsigned int  sys_mode=0;     		//当前设备工作模式

unsigned int charge_current_value=0x00;  //当前充电电流采样值

unsigned int discharge_current_value=0x00;  //当前负载电流采样值

unsigned int temperature_value=0x00;    //当前环境温度采样值

//----------------------参数设置

float light_pv=600;						//光控电压

float load_cc_I=33;						//LED灯工作电流  负载设定值


unsigned int step_01_load_percent=20;  		//节能输出百分比 20%

unsigned int step_02_load_percent=60;  		//节能输出百分比 60%

unsigned int step_03_load_percent=80;  		//节能输出百分比 80%

unsigned int step_04_load_percent=60;  		//节能输出百分比 60%

unsigned int step_05_load_percent=20;  		//节能输出百分比 20% 

unsigned int step_01_time_limit=0x01;   //时长 1 h

unsigned int step_02_time_limit=0x03;   //时长 3 h

unsigned int step_03_time_limit=0x04;   //时长 4 h

unsigned int step_04_time_limit=0x03;   //时长 3 h

unsigned int step_05_time_limit=0x01;   //时长 1 h

unsigned int  bt_id=1;						//电池类型  1：锂电池  2：铅酸电池

unsigned int light_time=1;						//光控时间：默认1分钟 单位(分钟)

float bt_00_hv=0;		//0天前电池电压最高值 (即今天)
float bt_00_lv=0;		//0天前电池电压最低值 (即今天)

float bt_01_hv=0;		//1天前电池电压最高值
float bt_01_lv=0;		//1天前电池电压最低值

float bt_02_hv=0;		//2天前电池电压最高值
float bt_02_lv=0;		//2天前电池电压最低值

float bt_03_hv=0;		//3天前电池电压最高值
float bt_03_lv=0;		//3天前电池电压最低值

float bt_04_hv=0;		//4天前电池电压最高值
float bt_04_lv=0;		//4天前电池电压最低值

float bt_05_hv=0;		//5天前电池电压最高值
float bt_05_lv=0;		//5天前电池电压最低值

float bt_06_hv=0;		//6天前电池电压最高值
float bt_06_lv=0;		//6天前电池电压最低值

float bt_07_hv=0;		//7天前电池电压最高值
float bt_07_lv=0;		//7天前电池电压最低值

float bt_dy[16]={0.0};

unsigned int yuyan_cnt=0x00;  //语言版本选择   00:汉语（默认）  01：英语


/**********************************************************************
*函数名称：read_param_eeprom
*描述：获取系统参数
*返回类型：void
*输入形参：void
***********************************************************************/
void read_param_eeprom(void)
{
	unsigned char byte_h,byte_l;
	//-----------------------------------
	byte_l=IapRead(0x0412);

	if(byte_l!=0x55)
	{
		IapErase(0x0400);	   //擦除0x0400起始扇区 512个字节

		IapProgram(0x0400, 0x02);
		IapProgram(0x0401, 0x58);	 //---光控电压

		IapProgram(0x0402, 0x00);
		IapProgram(0x0403, 0x21);	 //---负载电流

		IapProgram(0x0404, 0x64);

		IapProgram(0x0405, 0x64);

		IapProgram(0x0406, 0x64);

		IapProgram(0x0407, 0x64);

		IapProgram(0x0408, 0x64);

		IapProgram(0x040a, 0x01);

		IapProgram(0x040b, 0x00);

		IapProgram(0x040c, 0x05);

		IapProgram(0x040d, 0x05);

		IapProgram(0x040e, 0x01);

		IapProgram(0x040f, 0x01);

		IapProgram(0x0410, 0x01);

		IapProgram(0x0412, 0x55);  //---EEPROM 初始化标志位
	}
	//------------------------------------
	byte_h=IapRead(0x0400);
	
	byte_l=IapRead(0x0401);
		
	light_pv=(byte_h<<8)|byte_l;   //光控电压
	
	
	//------------------------------------
	byte_h=IapRead(0x0402);
	
	byte_l=IapRead(0x0403);
		
	load_cc_I=(byte_h<<8)|byte_l; //负载工作电流
	
	
	//------------------------------------
	byte_l=IapRead(0x0404);
								
	step_01_load_percent=byte_l;		 //第一阶段降载输出百分比
	
	//------------------------------------
	byte_l=IapRead(0x0405);
								
	step_02_load_percent=byte_l;		 //第二阶段降载输出百分比
	
	//------------------------------------
	byte_l=IapRead(0x0406);
								
	step_03_load_percent=byte_l;		 //第三阶段降载输出百分比
	
	//------------------------------------
	byte_l=IapRead(0x0407);
								
	step_04_load_percent=byte_l;		 //第四阶段降载输出百分比
	
	//------------------------------------
	byte_l=IapRead(0x0408);
								
	step_05_load_percent=byte_l;		 //第五阶段降载输出百分比
	
	//------------------------------------
	byte_l=IapRead(0x040a);
								
	bt_id=byte_l;						//系统电池类型!!!!!!
	//------------------------------------
	byte_l=IapRead(0x040b);
								
	light_time=byte_l;					//光控时间
	//------------------------------------
	byte_l=IapRead(0x040c);
								
	step_01_time_limit=byte_l;			//第一阶段时长
	//------------------------------------
	byte_l=IapRead(0x040d);
								
	step_02_time_limit=byte_l;			//第二一阶段时长
	//------------------------------------
	byte_l=IapRead(0x040e);
								
	step_03_time_limit=byte_l;			//第三一阶段时长
	//------------------------------------
	byte_l=IapRead(0x040f);
								
	step_04_time_limit=byte_l;			//第四一阶段时长
	//------------------------------------
	byte_l=IapRead(0x0410);
								
	step_05_time_limit=byte_l;			//第五阶段时长
	
	
}

void IapIdle()
{
    IAP_CONTR = 0;                              //关闭IAP功能
    IAP_CMD = 0;                                //清除命令寄存器
    IAP_TRIG = 0;                               //清除触发寄存器
    IAP_ADDRH = 0x80;                           //将地址设置到非IAP区域
    IAP_ADDRL = 0;
}

unsigned char IapRead(unsigned int addr)
{
    unsigned char dat;

    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 1;                                //设置IAP读命令
    IAP_ADDRL = addr;                           //设置IAP低地址
    IAP_ADDRH = addr >> 8;                      //设置IAP高地址
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();
    dat = IAP_DATA;                             //读IAP数据
    IapIdle();                                  //关闭IAP功能

    return dat;
}

void IapProgram(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 2;                                //设置IAP写命令
    IAP_ADDRL = addr;                           //设置IAP低地址
    IAP_ADDRH = addr >> 8;                      //设置IAP高地址
    IAP_DATA = dat;                             //写IAP数据
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();
    IapIdle();                                  //关闭IAP功能
}

void IapErase(unsigned int addr)
{
    IAP_CONTR = WT_24M;                         //使能IAP
    IAP_CMD = 3;                                //设置IAP擦除命令
    IAP_ADDRL = addr;                           //设置IAP低地址
    IAP_ADDRH = addr >> 8;                      //设置IAP高地址
    IAP_TRIG = 0x5a;                            //写触发命令(0x5a)
    IAP_TRIG = 0xa5;                            //写触发命令(0xa5)
    _nop_();                                    //
    IapIdle();                                  //关闭IAP功能
}



