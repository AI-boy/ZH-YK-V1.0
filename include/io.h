
#ifndef _ZH_IO_H
#define _ZH_IO_H


//**--------------包含文件-----------------------------------------------------

//**--------------宏定义-------------------------------------------------------
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

#define STAND     0		  //标准双向模式
#define PP_OUT 	  1		  //推挽输出模式
#define Z_IN      2		  //高阻输入模式
#define OD        3       //开漏模式


//电源控制

#define POWER_ON			(P35 = 0) 		// 输出低电平   开机
#define POWER_OFF			(P35 = 1) 		// 输出高电平   关机


//**--------------数据结构-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------


extern void init_port(void);

extern void set_io_mode(unsigned char port,unsigned char bit_n,unsigned char mode);
	


#endif 
