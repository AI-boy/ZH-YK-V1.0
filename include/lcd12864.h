 
#ifndef _ZH_LCD12864_H
#define _ZH_LCD12864_H


//**--------------包含文件-----------------------------------------------------

//**--------------宏定义-------------------------------------------------------



//lcd背光 LED

#define 	LCD_LED_OFF			(P26=1) 		// 输出高电平
#define 	LCD_LED_ON			(P26=0) 		// 输出低电平
#define 	LCD_LED_TOG			(P26^=1) 		// 输出反电平

//LCD端口


#define		LCD_CS    			P16
#define		LCD_RST   			P17
#define		LCD_RS    			P44
#define		LCD_SCK    			P15
#define		LCD_SDO    			P13





//**--------------数据结构-----------------------------------------------------

extern unsigned char a[];
extern unsigned char b[];
extern unsigned char c[];
extern unsigned char d[];
extern unsigned char e[];
extern unsigned char f[];

extern const unsigned char yunxing_jiemian[];
extern const unsigned char yunxing_jiemian_en[];
extern const unsigned char canshu_jiemian[];
extern const unsigned char canshu_jiemian_en[];

extern const unsigned char shuzi_1[];
extern const unsigned char shuzi_2[];
extern const unsigned char shuzi_3[];
extern const unsigned char shuzi_4[];
extern const unsigned char shuzi_5[];
extern const unsigned char shuzi_6[];
extern const unsigned char shuzi_7[];
extern const unsigned char shuzi_8[];
extern const unsigned char shuzi_9[];
extern const unsigned char fuhao_d[];
extern const unsigned char fuhao_m[];

extern const unsigned char hanzi_guang[];
extern const unsigned char hanzi_kong[];
extern const unsigned char hanzi_dian[];
extern const unsigned char hanzi_ya[];
extern const unsigned char hanzi_fu[];
extern const unsigned char hanzi_zai[];
extern const unsigned char hanzi_liu[];
extern const unsigned char hanzi_di[];
extern const unsigned char hanzi_yi[];
extern const unsigned char hanzi_er[];
extern const unsigned char hanzi_san[];
extern const unsigned char hanzi_si[];
extern const unsigned char hanzi_wu[];
extern const unsigned char hanzi_jie[];
extern const unsigned char hanzi_duan[];
extern const unsigned char hanzi_chi[];
extern const unsigned char hanzi_lei[];
extern const unsigned char hanzi_xing[];
extern const unsigned char hanzi_shi[];
extern const unsigned char hanzi_jian[];
extern const unsigned char hanzi_fu1[];
extern const unsigned char hanzi_shu[];
extern const unsigned char hanzi_chu[];
extern const unsigned char hanzi_chong[];
extern const unsigned char hanzi_gong[];
extern const unsigned char hanzi_zuo[];
extern const unsigned char hanzi_mo[];
extern const unsigned char hanzi_shi1[];


extern unsigned char buf[50];

//**--------------函数申明-----------------------------------------------------


extern void init_lcd(void);

extern void transfer_command(unsigned char dat);

extern void transfer_data(unsigned char dat);

extern void lcd_address(unsigned char page,unsigned char column);

extern void clear_screen(void);

extern void full_display(unsigned char data_left,unsigned char data_right);

extern void display_graphic_128x16(unsigned char page,unsigned char column,unsigned char *dp);

extern void display_graphic_32x32(unsigned char page,unsigned char column,unsigned char *dp);

extern void display_graphic_16x16(unsigned char page,unsigned char column,unsigned char reverse,unsigned char *dp);

extern void display_graphic_8x16(unsigned char page,unsigned char column,unsigned char *dp);

extern void display_graphic_8x8(unsigned char page,unsigned char column,unsigned char *dp);

extern void display_string_8x16(unsigned char page,unsigned char column,unsigned char *text);

extern void display_string_5x7(unsigned char page,unsigned char column,unsigned char *text);

extern void disp_grap(unsigned char page,unsigned char column,unsigned char *dp);

extern void disp_grap_xo(unsigned char page,unsigned char column,unsigned char *dp,unsigned char *dq);


	
extern void display_canshu(void);

extern void display_run_data(void);

























#endif 
