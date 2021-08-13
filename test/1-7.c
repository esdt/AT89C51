#include"reg51.h"
unsigned char a[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char count=0,num=0;

void initcount()
{
	TMOD=0x06;
	TH0=256-2;
	TL0=256-2;
	TR0=1;
	ET0=1;
	EA=1;
}


void display()
{
	P2=a[num];
	if(num==10)
	{
		num=0;
	}
}

void main()
{
	initcount();
	while(1)
	{
		display();
	}
}

void count_isr() interrupt 1
{
	num++;
}