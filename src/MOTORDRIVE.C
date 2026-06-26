#include <8052.h>
#include <MOTORDRIVE.H>

__sbit __at(0x91) ENMOTOR;        //ENABLEA
__sbit __at(0x92) MOTOR1;         //IN2
__sbit __at(0x93) MOTOR2;         //pwm pin

void InitMotor()
{
	ENMOTOR=0;              //stop motor
	MOTOR1=1;
	MOTOR2=1;
}
void ENMotor()
{
	MOTOR1=0;
	MOTOR2=0;
	ENMOTOR=1;
}