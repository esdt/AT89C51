#include"reg51.h"
unsigned char a[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char count=0,num=0;
sbit ex=P3^2;
void initex()
{
   IT0=1;
   EX0=1;
   //IE0=1;
   EA=1;
   //ex=1;
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
	initex();
	while(1)
	{
		display();
	}
}

void ex_isr() interrupt 0
{
	num++;
}