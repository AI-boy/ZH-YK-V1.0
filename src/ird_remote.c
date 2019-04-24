//**--------------ͷ�ļ�-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------ȫ�ֱ���-----------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------




//ϵͳ����״̬���ݼ����ò���
//------------------------------------------------------------------------------//
//		__EEPROM_DATA(0x02, 0x58, 0x00, 0x21, 0x14, 0x3C, 0x50, 0x3C);
//		
//		__EEPROM_DATA(0x14, 0x01, 0x01, 0x01, 0x01, 0x03, 0x04, 0x03);
//		
//		__EEPROM_DATA(0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
//------------------------------------------------------------------------------//
//-----------------------��������
float p_v=0;    						//��ǰ�����ѹ

float b_v=0;							//��ǰ��ص�ѹ

float load_v=0;							//��ǰ���ص�ѹ

float charge_I =0; 						//��ǰ������

float load_I =0;    					//��ǰ���ص���

unsigned int  sys_mode=0;     		//��ǰ�豸����ģʽ

unsigned int charge_current_value=0x00;  //��ǰ����������ֵ

unsigned int discharge_current_value=0x00;  //��ǰ���ص�������ֵ

unsigned int temperature_value=0x00;    //��ǰ�����¶Ȳ���ֵ

//----------------------��������

float light_pv=600;						//��ص�ѹ

float load_cc_I=33;						//LED�ƹ�������  �����趨ֵ


unsigned int step_01_load_percent=20;  		//��������ٷֱ� 20%

unsigned int step_02_load_percent=60;  		//��������ٷֱ� 60%

unsigned int step_03_load_percent=80;  		//��������ٷֱ� 80%

unsigned int step_04_load_percent=60;  		//��������ٷֱ� 60%

unsigned int step_05_load_percent=20;  		//��������ٷֱ� 20% 

unsigned int step_01_time_limit=0x01;   //ʱ�� 1 h

unsigned int step_02_time_limit=0x03;   //ʱ�� 3 h

unsigned int step_03_time_limit=0x04;   //ʱ�� 4 h

unsigned int step_04_time_limit=0x03;   //ʱ�� 3 h

unsigned int step_05_time_limit=0x01;   //ʱ�� 1 h

unsigned int  bt_id=1;						//�������  1��﮵��  2��Ǧ����

unsigned int light_time=1;						//���ʱ�䣺Ĭ��1���� ��λ(����)

float bt_00_hv=0;		//0��ǰ��ص�ѹ���ֵ (������)
float bt_00_lv=0;		//0��ǰ��ص�ѹ���ֵ (������)

float bt_01_hv=0;		//1��ǰ��ص�ѹ���ֵ
float bt_01_lv=0;		//1��ǰ��ص�ѹ���ֵ

float bt_02_hv=0;		//2��ǰ��ص�ѹ���ֵ
float bt_02_lv=0;		//2��ǰ��ص�ѹ���ֵ

float bt_03_hv=0;		//3��ǰ��ص�ѹ���ֵ
float bt_03_lv=0;		//3��ǰ��ص�ѹ���ֵ

float bt_04_hv=0;		//4��ǰ��ص�ѹ���ֵ
float bt_04_lv=0;		//4��ǰ��ص�ѹ���ֵ

float bt_05_hv=0;		//5��ǰ��ص�ѹ���ֵ
float bt_05_lv=0;		//5��ǰ��ص�ѹ���ֵ

float bt_06_hv=0;		//6��ǰ��ص�ѹ���ֵ
float bt_06_lv=0;		//6��ǰ��ص�ѹ���ֵ

float bt_07_hv=0;		//7��ǰ��ص�ѹ���ֵ
float bt_07_lv=0;		//7��ǰ��ص�ѹ���ֵ

float bt_dy[16]={0.0};

unsigned int yuyan_cnt=0x00;  //���԰汾ѡ��   00:���Ĭ�ϣ�  01��Ӣ��


/**********************************************************************
*�������ƣ�read_param_eeprom
*��������ȡϵͳ����
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void read_param_eeprom(void)
{
	unsigned char byte_h,byte_l;
	//-----------------------------------
	byte_l=IapRead(0x0412);

	if(byte_l!=0x55)
	{
		IapErase(0x0400);	   //����0x0400��ʼ���� 512���ֽ�

		IapProgram(0x0400, 0x02);
		IapProgram(0x0401, 0x58);	 //---��ص�ѹ

		IapProgram(0x0402, 0x00);
		IapProgram(0x0403, 0x21);	 //---���ص���

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

		IapProgram(0x0412, 0x55);  //---EEPROM ��ʼ����־λ
	}
	//------------------------------------
	byte_h=IapRead(0x0400);
	
	byte_l=IapRead(0x0401);
		
	light_pv=(byte_h<<8)|byte_l;   //��ص�ѹ
	
	
	//------------------------------------
	byte_h=IapRead(0x0402);
	
	byte_l=IapRead(0x0403);
		
	load_cc_I=(byte_h<<8)|byte_l; //���ع�������
	
	
	//------------------------------------
	byte_l=IapRead(0x0404);
								
	step_01_load_percent=byte_l;		 //��һ�׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=IapRead(0x0405);
								
	step_02_load_percent=byte_l;		 //�ڶ��׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=IapRead(0x0406);
								
	step_03_load_percent=byte_l;		 //�����׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=IapRead(0x0407);
								
	step_04_load_percent=byte_l;		 //���Ľ׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=IapRead(0x0408);
								
	step_05_load_percent=byte_l;		 //����׶ν�������ٷֱ�
	
	//------------------------------------
	byte_l=IapRead(0x040a);
								
	bt_id=byte_l;						//ϵͳ�������!!!!!!
	//------------------------------------
	byte_l=IapRead(0x040b);
								
	light_time=byte_l;					//���ʱ��
	//------------------------------------
	byte_l=IapRead(0x040c);
								
	step_01_time_limit=byte_l;			//��һ�׶�ʱ��
	//------------------------------------
	byte_l=IapRead(0x040d);
								
	step_02_time_limit=byte_l;			//�ڶ�һ�׶�ʱ��
	//------------------------------------
	byte_l=IapRead(0x040e);
								
	step_03_time_limit=byte_l;			//����һ�׶�ʱ��
	//------------------------------------
	byte_l=IapRead(0x040f);
								
	step_04_time_limit=byte_l;			//����һ�׶�ʱ��
	//------------------------------------
	byte_l=IapRead(0x0410);
								
	step_05_time_limit=byte_l;			//����׶�ʱ��
	
	
}

void IapIdle()
{
    IAP_CONTR = 0;                              //�ر�IAP����
    IAP_CMD = 0;                                //�������Ĵ���
    IAP_TRIG = 0;                               //��������Ĵ���
    IAP_ADDRH = 0x80;                           //����ַ���õ���IAP����
    IAP_ADDRL = 0;
}

unsigned char IapRead(unsigned int addr)
{
    unsigned char dat;

    IAP_CONTR = WT_24M;                         //ʹ��IAP
    IAP_CMD = 1;                                //����IAP������
    IAP_ADDRL = addr;                           //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;                      //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                            //д��������(0x5a)
    IAP_TRIG = 0xa5;                            //д��������(0xa5)
    _nop_();
    dat = IAP_DATA;                             //��IAP����
    IapIdle();                                  //�ر�IAP����

    return dat;
}

void IapProgram(unsigned int addr, unsigned char dat)
{
    IAP_CONTR = WT_24M;                         //ʹ��IAP
    IAP_CMD = 2;                                //����IAPд����
    IAP_ADDRL = addr;                           //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;                      //����IAP�ߵ�ַ
    IAP_DATA = dat;                             //дIAP����
    IAP_TRIG = 0x5a;                            //д��������(0x5a)
    IAP_TRIG = 0xa5;                            //д��������(0xa5)
    _nop_();
    IapIdle();                                  //�ر�IAP����
}

void IapErase(unsigned int addr)
{
    IAP_CONTR = WT_24M;                         //ʹ��IAP
    IAP_CMD = 3;                                //����IAP��������
    IAP_ADDRL = addr;                           //����IAP�͵�ַ
    IAP_ADDRH = addr >> 8;                      //����IAP�ߵ�ַ
    IAP_TRIG = 0x5a;                            //д��������(0x5a)
    IAP_TRIG = 0xa5;                            //д��������(0xa5)
    _nop_();                                    //
    IapIdle();                                  //�ر�IAP����
}



