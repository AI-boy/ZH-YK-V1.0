
//**--------------ͷ�ļ�-------------------------------------------------------
#include "STC8.h"
#include "intrins.h"

#include <stdio.h>
#include <string.h>

#include "userdefine.h"	

//**--------------ȫ�ֱ���-----------------------------------------------------

//**--------------��������-----------------------------------------------------

//**--------------��������-----------------------------------------------------


/**********************************************************************
*�������ƣ�init_time0
*��������ʼ��ϵͳʱ����ʱ�� 1ms
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void init_timer0(void)
{
   AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
   TMOD &= 0xF0;		//���ö�ʱ��ģʽ
   TH0 = 0xF8;								   //��ʱ��ʱ��Ƶ�ʣ�FOSC/12=24M/12=2MHz
   TL0 = 0x30;                                 //(65536-63536)=2000 * 1/2000000=1ms
   ET0 = 0;                                    //��ֹ��ʱ��0�ж�
   EA = 0;									   //ȫ���ж�
   TF0=0;
   TR0 = 0;                                    //������ʱ��
  
}