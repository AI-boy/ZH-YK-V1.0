
#ifndef _ZH_LED_H
#define _ZH_LED_H


//**--------------包含文件-----------------------------------------------------

//**--------------宏定义-------------------------------------------------------



//照明LED

#define LED_ON			(P12= 1) 		//	亮灯
#define LED_OFF			(P12= 0) 		// 	关灯
#define LED_TOG			(P12^=1)









//**--------------数据结构-----------------------------------------------------

//**--------------函数申明-----------------------------------------------------


extern void init_led(void);
	


#endif 
