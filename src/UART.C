#include <8052.h>
#include <UART.h>
#include <string.h>


unsigned char irbuff = 0;
unsigned char  UsartReadCnt = 0; 
unsigned char  UsartReadBuff[4];
bit RI_Flag = 0;
bit Start_Flag = 0;
bit Reset_Flag = 0;
bit open_loop = 0;
bit close_loop = 0;
bit speed_flag = 0;
bit temp_flag = 0;
unsigned int uSpeed = 0;
bit U_Flag = 0;

/*************波特率配置函数********************/

void UART_init(unsigned int baud)
{
	
	SCON = 0x50;                              //工作在方式1    8位UART,波特率可调
	PCON = 0X80;                            
	AUXR = 0x11;                             //使用独立波特率发生器，处于12T模式
	
	BTR = 256-(11059200/6/32)/baud;
	ES = 1;
	/******因为有串口和定时器中断，设置串口中断为最高优先级*****/
	PS = 1;
}

void SendByte(unsigned char dat)
{
	SBUF = dat;		 //把要发送的dat数据写入SBUF
	while(TI==0);	     //等待数据发送完成
	TI=0; //清除标志位
}

//void SendString(unsigned char *p)     //串口发送一个字符串
//{
//	while(*p)
//	{
//		SendByte(*p);
//		p++;
//	}
//}

void uart() interrupt 4
{
	if(RI)
	{
//		unsigned char i = 0;
		RI = 0;
		irbuff = SBUF;
		if(irbuff == 0xEE)	      // START
		{
			Start_Flag = 1;
		}
		else if(irbuff == 0xED)     // STOP
		{
			RI_Flag = 1;				
		}
		else if(irbuff == 0xEC)	     //  RESET
		{
			Reset_Flag = 1; 	
		}
		else if(irbuff == 0xEA)  	// open loop
		{
			open_loop = 1;	
		}
		else if(irbuff == 0xEB)	   // close loop
		{
			close_loop = 1;
		}
		else if(irbuff == 0xDE)		// speed
		{
		 	speed_flag = 1;
		}
		else if(irbuff == 0xDF)		// temperature
		{
			temp_flag = 1;
		}
		else
		{
			UsartReadBuff[UsartReadCnt] = irbuff;
			UsartReadCnt++;		
		}
		if(UsartReadCnt == 3)
		{
			UsartReadCnt = 0;
			uSpeed = (UsartReadBuff[0]-0x30)*100+(UsartReadBuff[1]-0x30)*10+(UsartReadBuff[2]-0x30);
			U_Flag = 1;				
		}				
	}
}

void  SendData(unsigned int dat)               //发送的次序是人为定的协议
{
	unsigned char Lbyte,Hbyte;
	Hbyte = dat>>8;
	Lbyte = dat&0x00ff;
	SendByte(0xFF);
	SendByte(Lbyte);
	SendByte(Hbyte);
}

//void  SendData(unsigned int dat)               //发送的次序是人为定的协议
//{
//	unsigned char Lbyte,Hbyte;
//	Hbyte = dat>>8;
//	Lbyte = dat&0x00ff;
//	SendByte(Lbyte);
//	SendByte(Hbyte);
//}