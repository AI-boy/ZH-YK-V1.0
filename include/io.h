
#ifndef _ZH_IO_H
#define _ZH_IO_H


//**--------------�����ļ�-----------------------------------------------------

//**--------------�궨��-------------------------------------------------------
#define PORT0    0
#define PORT1    1
#define PORT2    2
#define PORT3    3
#define PORT4    4
#define PORT5    5
#define PORT6    6
#define PORT7    7


#define BIT0     (0)
#define BIT1     (1)
#define BIT2     (2)
#define BIT3     (3)
#define BIT4     (4)
#define BIT5     (5)
#define BIT6     (6)
#define BIT7     (7)

#define STAND     0		  //��׼˫��ģʽ
#define PP_OUT 	  1		  //�������ģʽ
#define Z_IN      2		  //��������ģʽ
#define OD        3       //��©ģʽ


//��Դ����

#define POWER_ON			(P35 = 0) 		// ����͵�ƽ   ����
#define POWER_OFF			(P35 = 1) 		// ����ߵ�ƽ   �ػ�


//**--------------���ݽṹ-----------------------------------------------------

//**--------------��������-----------------------------------------------------


extern void init_port(void);

extern void set_io_mode(unsigned char port,unsigned char bit_n,unsigned char mode);
	


#endif 
