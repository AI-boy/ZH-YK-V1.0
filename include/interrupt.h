
#ifndef _ZH_INTERRUPT_H
#define _ZH_INTERRUPT_H

//**--------------�����ļ�-----------------------------------------------------

//**--------------�궨��-------------------------------------------------------

 #define   TX1IF       TI

 #define   RX1IF       RI

 #define   TX2IF       (S2CON&0x02)   

 #define   RX2IF       (S2CON&0x01)   

 #define   TX3IF       (S3CON&0x02)  

 #define   RX3IF       (S3CON&0x01)   

 #define   TX4IF       (S4CON&0x02)   

 #define   RX4IF       (S4CON&0x01)	

//**--------------���ݽṹ-----------------------------------------------------

//**--------------��������-----------------------------------------------------
extern void init_interrupt(void);
	
//**--------------ȫ�ֱ���-----------------------------------------------------



extern unsigned char system_run_time;

extern unsigned int system_time_count;

extern unsigned int display_lcd_time_count;
							
extern unsigned char display_lcd_flag;

extern unsigned char dat_flag;









#endif 
