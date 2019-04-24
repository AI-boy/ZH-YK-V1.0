  
#ifndef _ZH_KEY_H
#define _ZH_KEY_H


//**--------------宏定义-----------------------------------------------------


//#define	  K1_GET	(P25)      
//#define	  K2_GET	(P24)
//#define	  K3_GET	(P23)
//#define	  K4_GET	(P22)
//#define	  K5_GET	(P21)
//#define	  K6_GET	(P42)
//#define	  K7_GET	(P20)
//#define	  K8_GET	(P41)
//#define	  K9_GET	(P37)
//#define	  K10_GET	(P36)
//#define	  K11_GET	(P51)
//#define	  K12_GET	(P50)


#define	  K1_GET	(P21)      
#define	  K2_GET	(P42)
#define	  K3_GET	(P25)
#define	  K4_GET	(P50)
#define	  K5_GET	(P20)
#define	  K6_GET	(P24)
#define	  K7_GET	(P51)
#define	  K8_GET	(P41)
#define	  K9_GET	(P23)
#define	  K10_GET	(P36)
#define	  K11_GET	(P37)
#define	  K12_GET	(P22)


//**--------------数据结构-------------------------------------------------------


typedef enum KEY_CURRENT_STATE
       {
         KEY_UP  =0x00,
         KEY_DOWN=0x01
       } KEY_STATE_NU ;

typedef enum KEY_CURRENT_VALUE
       {
         KNOP =0x10,
         K1   =0x01,
         K2   =0x02,
         K3   =0x03,
         K4   =0x04,
         K5   =0x05,
         K6   =0x06,
         K7   =0x07,
         K8   =0x08,
         K9   =0x09, 
         K10  =0x0A,
         K11  =0x0B, 
         K12  =0x0C           
       } KEY_VALUE_NU ;


//**--------------全局声明-------------------------------------------------------



extern KEY_STATE_NU  KEY_STATE;

extern KEY_VALUE_NU  KEY_VALUE;


extern unsigned char scan_key_time_count;

extern unsigned char handle_scan_key_flag;

extern unsigned char menu_index_q;

extern unsigned char zhuangtai_cnt;

extern unsigned char canshu_cnt;

extern unsigned char key1_time_count;

extern unsigned char canshu_1_weizhi;

extern unsigned char canshu_2_weizhi;

extern unsigned char canshu_3_weizhi;

extern unsigned char canshu_4_weizhi;

extern unsigned char canshu_5_weizhi;

extern unsigned char canshu_6_weizhi;

extern unsigned char canshu_7_weizhi;

extern unsigned char canshu_8_weizhi;

extern unsigned char canshu_9_weizhi;

extern unsigned char canshu_10_weizhi;

extern unsigned char canshu_11_weizhi;

extern unsigned char canshu_12_weizhi;

extern unsigned char canshu_13_weizhi;

extern unsigned char canshu_14_weizhi;

extern unsigned char poll_time_enable;

extern unsigned char poll_task_flag;

extern unsigned int poll_time_count;

extern unsigned char set_status;

extern unsigned int work_mode;

extern unsigned int day_index;


extern 	bit    key1_status;

extern 	bit    key2_status;

extern 	bit    key3_status;

extern 	bit    key4_status;

extern 	bit    key5_status;

extern 	bit    key6_status;

extern 	bit    key7_status;

extern 	bit    key8_status;

extern 	bit    key9_status;

extern 	bit    key10_status;

extern 	bit    key11_status;

extern 	bit    key12_status;







extern void init_key(void);

extern void scan_key_value(void);

























	


#endif 
