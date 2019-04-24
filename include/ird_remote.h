 #ifndef _IRD_REMOTE_H
 #define _IRD_REMOTE_H





#define WT_30M          0x80
#define WT_24M          0x81
#define WT_20M          0x82
#define WT_12M          0x83
#define WT_6M           0x84
#define WT_3M           0x85
#define WT_2M           0x86
#define WT_1M           0x87


//��������
extern float p_v;

extern float b_v;

extern float load_v;

extern float charge_I;

extern float load_I;

extern unsigned int sys_mode;

extern unsigned int charge_current_value;  //��ǰ����������ֵ

extern unsigned int discharge_current_value;  //��ǰ���ص�������ֵ

extern unsigned int temperature_value;    //��ǰ�����¶Ȳ���ֵ

extern float light_pv;

extern float load_cc_I;


extern unsigned int step_01_load_percent;  		//��������ٷֱ� 20%

extern unsigned int step_02_load_percent;  		//��������ٷֱ� 60%

extern unsigned int step_03_load_percent;  		//��������ٷֱ� 80%

extern unsigned int step_04_load_percent;  		//��������ٷֱ� 60%

extern unsigned int step_05_load_percent;  		//��������ٷֱ� 20%

extern unsigned int  step_01_time_limit;   //ʱ�� 1 h

extern unsigned int  step_02_time_limit;   //ʱ�� 3 h

extern unsigned int  step_03_time_limit;   //ʱ�� 4 h

extern unsigned int  step_04_time_limit;   //ʱ�� 3 h

extern unsigned int  step_05_time_limit;   //ʱ�� 1 h

extern unsigned int bt_id;						//�������  1��﮵��  2��Ǧ����

extern unsigned int light_time;					//���ʱ�䣺Ĭ��1���� ��λ(����)


extern float bt_00_hv;		//0��ǰ��ص�ѹ���ֵ (������)
extern float bt_00_lv;		//0��ǰ��ص�ѹ���ֵ (������)

extern float bt_01_hv;		//1��ǰ��ص�ѹ���ֵ
extern float bt_01_lv;		//1��ǰ��ص�ѹ���ֵ

extern float bt_02_hv;		//2��ǰ��ص�ѹ���ֵ
extern float bt_02_lv;		//2��ǰ��ص�ѹ���ֵ

extern float bt_03_hv;		//3��ǰ��ص�ѹ���ֵ
extern float bt_03_lv;		//3��ǰ��ص�ѹ���ֵ

extern float bt_04_hv;		//4��ǰ��ص�ѹ���ֵ
extern float bt_04_lv;		//4��ǰ��ص�ѹ���ֵ

extern float bt_05_hv;		//5��ǰ��ص�ѹ���ֵ
extern float bt_05_lv;		//5��ǰ��ص�ѹ���ֵ

extern float bt_06_hv;		//6��ǰ��ص�ѹ���ֵ
extern float bt_06_lv;		//6��ǰ��ص�ѹ���ֵ

extern float bt_07_hv;		//7��ǰ��ص�ѹ���ֵ
extern float bt_07_lv;		//7��ǰ��ص�ѹ���ֵ

extern float bt_dy[16];

extern unsigned int yuyan_cnt;  //���԰汾ѡ��




extern void read_param_eeprom(void);


extern void IapIdle();

extern unsigned char IapRead(unsigned int addr);

extern void IapProgram(unsigned int addr, unsigned char dat);

extern void IapErase(unsigned int addr);




#endif
