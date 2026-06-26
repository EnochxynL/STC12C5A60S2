#ifndef _UART_H_
#define _UART_H_


__sfr __at(0x8E) AUXR;
__sfr __at(0x9C) BTR;

extern __bit RI_Flag;
extern __bit Start_Flag;
extern __bit Reset_Flag;
extern __bit close_loop;
extern __bit open_loop;
extern unsigned int uSpeed;
extern __bit U_Flag;
extern __bit speed_flag;
extern __bit temp_flag;

void UART_init(unsigned int baud);
//unsigned char GetByte(void);
void  SendData(unsigned int dat);
void  SendByte(unsigned char dat);
//void SendString(unsigned char *p);

#endif