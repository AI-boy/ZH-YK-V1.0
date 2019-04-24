 
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
*�������ƣ�init_pwm
*������PWM7  P2.7    
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void init_pwm(void)
{

	
	//----------------------------�����ز�Ƶ��38kHz   
	
	 set_io_mode(PORT2,7,STAND);	//P2.7  ˫��˿�    PWM7   

	 P27 = 0;						//PWM IO����� �͵�ƽ

	 P_SW2 |= EAXFR;

     PWMCKS = 0x00;                             //PWMʱ��Ϊϵͳʱ�� 24MHZ
     PWMC   = PWM_MAX_DUTY;                     //����PWM����Ϊ1200��PWMʱ�� 24MHZ/624=38.5KHz
	  											//PWM7 ���� ռ�ձ�����	  Ĭ��1:3
     PWM7T1 = 208;                             	//�ڼ���ֵΪ208H�ط�����͵�ƽ
     PWM7T2 = 0;                             	//�ڼ���ֵΪ0H�ط�����ߵ�ƽ
     PWM7CR |= ENC7O;                           //ʹ��PWM7ͨ�����
	 PWM7CR |= 0x40;							//����˿ڳ�ʼ��ƽ��Ϊ�ߵ�ƽ


     P_SW2 &= ~EAXFR;

     PWMCR = 0x00;                               //��ʼ��PWMģ��ʱ ��ֹ״̬
	
}

/**********************************************************************
*�������ƣ�Enable_pwm
*������
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Enable_pwm(void)
{
	P_SW2 |= EAXFR;

	PWM7CR |= ENC7O;
	PWM7CR |= 0x40;							//����˿ڳ�ʼ��ƽ��Ϊ�ߵ�ƽ

	P_SW2 &= ~EAXFR;

	PWMCR |= 0x80;							 //����PWMģ��
	
}

/**********************************************************************
*�������ƣ�disable_pwm
*������
*�������ͣ�void
*�����βΣ�void
***********************************************************************/
void Disable_pwm(void)
{
	P_SW2 |= EAXFR;

	PWM7CR &= ~ENC7O;
	PWM7CR &= ~0x40;				//����˿ڳ�ʼ��ƽ��Ϊ�͵�ƽ

	P_SW2 &= ~EAXFR;

	PWMCR &= ~0x80;					//�ر�PWMģ��

	set_io_mode(PORT2,7,STAND);	    //P2.7  ˫��˿�    PWM7   

	P27 = 0;					    //PWM IO����� �͵�ƽ

}

