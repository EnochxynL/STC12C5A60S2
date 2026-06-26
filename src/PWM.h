#ifndef _PWM_H_
#define _PWM_H_



__sfr __at(0xD8) CCON; //PCA control register
__sfr __at(0xD9) CMOD; //PCA mode register
__sfr __at(0xDA) CCAPM0; //PCA module-0 mode register
__sfr __at(0xDB) CCAPM1; //PCA module-1 mode register
__sfr __at(0xE9) CL; //PCA base timer LOW
__sfr __at(0xF9) CH; //PCA base timer HIGH
__sfr __at(0xEA) CCAP0L; //PCA module-0 capture register LOW
__sfr __at(0xFA) CCAP0H; //PCA module-0 capture register HIGH
__sfr __at(0xEB) CCAP1L; //PCA module-1 capture register LOW
__sfr __at(0xFB) CCAP1H; //PCA module-1 capture register HIGH
__sfr __at(0xF2) PCAPWM0;
__sfr __at(0xF3) PCAPWM1;
__sbit __at(0xDE) CR; //PCA timer run control bit
__sbit __at(0xDF) CF; //PCA timer overflow flag
__sbit __at(0xD8) CCF0; //PCA module-0 interrupt flag
__sbit __at(0xD9) CCF1; //PCA module-1 interrupt flag

__sfr __at(0x91) P1M1;            //配置I/O模式见手册87页
__sfr __at(0x92) P1M0;


void SetPWM1(unsigned char pwm);
void ClosePWM1();
void Port_init();
void PWM_init();
void ClosePWM0();
void InitPWM(void);
void PWM0_Setting(unsigned char pwm);

#endif