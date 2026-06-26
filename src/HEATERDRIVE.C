#include <8052.h>
#include <HEATERDRIVE.H>

__sbit __at(0x96) ENHEATER;
__sbit __at(0x94) HEATER1;     //PWM1
__sbit __at(0x95) HEATER2;

void Heater_Init(void)
{
	ENHEATER=0;
	HEATER1=1;
	HEATER2=1;
}
void ENHeater(void)
{
	ENHEATER=1;
	HEATER1=0;
	HEATER2=0;
}