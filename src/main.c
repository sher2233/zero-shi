
#include "reg52.h"
#include "intrins.h"

typedef unsigned int u16;	
typedef unsigned char u8;

sbit KEY1=P3^1;
sbit KEY2=P3^0;
sbit KEY3=P3^2;
sbit KEY4=P3^3;

#define KEY1_PRESS	1
#define KEY2_PRESS	2
#define KEY3_PRESS	3
#define KEY4_PRESS	4
#define KEY_UNPRESS	0	

u16 LEDMode=1;

void time1_init()
{
	TMOD|=0X10;
	TH1=0XFC;//定时器赋初值，1ms	
	TL1=0X18;	
	ET1=1;
	EA=1;
	TR1=1;	
}

void delay_10us(u16 ten_us)//延时函数
{
	while(ten_us--);	
}

u8 key_scan()
{
	if(KEY1==0)
	{
		delay_10us(100);
		while(KEY1==0)
		delay_10us(100);
		return KEY1_PRESS;
	}
	if(KEY2==0)
	{
		delay_10us(100);
		while(KEY2==0)
		delay_10us(100);
		return KEY2_PRESS;
	}
}

void main()
{
	P2=0xFE;
	time1_init();
	while(1)
	{
		if(key_scan())
		{
			if(key_scan()==KEY1_PRESS)LEDMode=KEY1_PRESS;
			if(key_scan()==KEY2_PRESS)LEDMode=KEY2_PRESS;
		}
	}
}

void time1() interrupt 3
{
	static unsigned int count=0;
	TH1=0XFC;//定时器赋初值，1ms	
	TL1=0X18;
	count++;
	if(count>=500)
	{
		count=0;
		if(LEDMode==1)
		P2=_cror_(P2,1);
		if(LEDMode==2)
		P2=_crol_(P2,1);
	}
}
	