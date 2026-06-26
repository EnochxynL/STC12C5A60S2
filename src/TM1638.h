#ifndef _TM1638_H
#define _TM1638_H
/***********************************************
File name  ：TM1638.h
Author     ：YQ
Version    ：V1.1
Describe   ：The command line of the TM1638
**************************************************/
__sbit __at(0xA0) DIO;                                 /* TM1638数据口 */
__sbit __at(0xA1) CLK;                                 /* TM1638时钟信号 */
__sbit __at(0xA2) STB;                                 /* TM1638片选 */

/******************Address Command*****************************/
#define     TM1638_DIG0                 0XC0
#define     TM1638_DIG1                 0XC2
#define     TM1638_DIG2                 0XC4
#define     TM1638_DIG3                 0XC6
#define     TM1638_DIG4                 0XC8
#define     TM1638_DIG5                 0XCA
#define     TM1638_DIG6                 0XCC
#define     TM1638_DIG7                 0XCE

void TM1638_WriteData( unsigned char DATA );
void Write_Command(unsigned char cmd);
void Write_DATA(unsigned char add,unsigned char DATA1);
void TM1638_Init();
#endif