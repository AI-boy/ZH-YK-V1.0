
#ifndef _ZH_UART_H
#define _ZH_UART_H

//**--------------�����ļ�-----------------------------------------------------

//**--------------�궨��-------------------------------------------------------





#define  IRD_BY_UART	1


//**--------------���ݽṹ-----------------------------------------------------

//**--------------��������-----------------------------------------------------
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


extern unsigned char tx1_mt;   //UART1���ͼĴ���������ɱ�־

extern unsigned char tx2_mt;	 //UART2���ͼĴ���������ɱ�־

extern unsigned char tx3_mt;	 //UART3���ͼĴ���������ɱ�־

extern unsigned char tx4_mt;	 //UART4���ͼĴ���������ɱ�־

extern unsigned char rx1_mt;   //UART1���ܼĴ���������ɱ�־

extern unsigned char rx2_mt;	 //UART2���ܼĴ���������ɱ�־

extern unsigned char rx3_mt;	 //UART3���ܼĴ���������ɱ�־

extern unsigned char rx4_mt;	 //UART4���ܼĴ���������ɱ�־


extern unsigned char uart2_rx_buf[80];

extern unsigned char uart2_tx_buf[80];


extern unsigned char rx_frame_kind;  //����֡ ���  01--��������֡		02--��������֡		03--�������淵��ȷ��֡
extern unsigned char tx_frame_kind; //����֡




extern unsigned char uart2_time_count;

extern unsigned char uart2_receive_byte_count;

extern unsigned char uart2_receive_flag;




#endif 