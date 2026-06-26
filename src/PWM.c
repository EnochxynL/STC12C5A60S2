#include <reg51.h>
#include <intrins.h>
#include <PWM.h>


/******P1.3和P1.4*******/
void Port_init()
{
	P1M1=0x00;    //配置P1各个端口的模式，用P1M1的第一位和P1M0的第一位共同控制P1^1口，依此类推
	P1M0=0x00;
}
// PWM
void PWM_init(void)
{
	CCON = 0X00;
	CH = 0X00;
	CL = CH;
	CMOD = 0X02;    //TIMER CLOCK RESORCE 
}
//// 温度PWM
//void InitPWM(void)
//{
//	CCON&=0X00;//CF=0;CR=0;CCFn=0;
//	CH=0X00;
//	CL=CH;
//	CMOD=0X02;//  TIMER CLOCK RESORCE 0X02---(1/2)FOSC;0X08---1FOSC;0X00---(1/12)FOSC
//}

void PWM0_Setting(unsigned char pwm)
{

		 CCAP0H = 255-pwm;
		 CCAP0L = CCAP0H;
	 
		 CCAPM0 = 0X42;     //CCAPMn寄存器的PWMn和ECOMn必须置位
		 CR = 1;            //PWM 启动    这个位必须置1！！！
}

void ClosePWM0()
{
	CCAPM0=0;
}

void SetPWM1(unsigned char pwm)
{

	CCAP1H = 255-pwm;
	CCAP1L = CCAP1H;
	CCAPM1 = 0X42;
	CR = 1;
}

void ClosePWM1()
{
	CCAPM1=0;
}