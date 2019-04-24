
#ifndef _ZH_UART_H
#define _ZH_UART_H

//**--------------包含文件-----------------------------------------------------

//**--------------宏定义-------------------------------------------------------





#define  IRD_BY_UART	1


//**--------------数据结构-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------
extern void init_uart2(void);
	
extern void uart2_send_byte(unsigned char dat);

extern void uart2_send_nbyte(unsigned char *dat,unsigned int size);
	
extern unsigned char uart2_read_byte(void);
	
extern void uart2_read_nbyte(unsigned char *buffer,unsigned char length);	

extern bit handle_even_check(unsigned char databyte);
	
extern void handle_uart2_rx_buf(void);		

extern void  read_run_data(void);

extern void read_sys_parameter(void);

extern void save_sys_parameter(void);


extern unsigned char tx1_mt;   //UART1发送寄存器发送完成标志

extern unsigned char tx2_mt;	 //UART2发送寄存器发送完成标志

extern unsigned char tx3_mt;	 //UART3发送寄存器发送完成标志

extern unsigned char tx4_mt;	 //UART4发送寄存器发送完成标志

extern unsigned char rx1_mt;   //UART1接受寄存器接受完成标志

extern unsigned char rx2_mt;	 //UART2接受寄存器接受完成标志

extern unsigned char rx3_mt;	 //UART3接受寄存器接受完成标志

extern unsigned char rx4_mt;	 //UART4接受寄存器接受完成标志


extern unsigned char uart2_rx_buf[80];

extern unsigned char uart2_tx_buf[80];


extern unsigned char rx_frame_kind;  //接受帧 类别  01--运行数据帧		02--参数数据帧		03--参数保存返回确认帧
extern unsigned char tx_frame_kind; //发送帧




extern unsigned char uart2_time_count;

extern unsigned char uart2_receive_byte_count;

extern unsigned char uart2_receive_flag;




#endif 