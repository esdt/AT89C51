#include"reg51.h"
#define uint unsigned int
sbit IN1 = P2^0;
sbit IN2 = P2^1;
sbit EN = P2^2;
uint value[] = {2000,8000};
uint count = 0; 
//void delay(uint n)
//{
// 	uint i=0,j=0;
//	for(i=0;i<n;i++)
//	{
//		for(j=0;j<120;j++);
//	}
//}

void inittimer()
{
	TMOD=0X01;
	TH0=(65536-8000)/256; //��ֵ�����ƶ�8λ
	TL0=(65536-8000)%256;//��ֵ�����ƶ�8λ		 10ms=10000us
	ET0=1; //��ʱ��/������T0������ж�����λ
	EA=1; //�ж������ܿ�λ
	TR0=1;	//������ʱ��
	IN1=0;
}

void motor()
{
	IN1=0;
//	IN2=1;
//	delay(25);
//	IN2=0;
//	delay(25);
	EN=1;
}

void main()
{	
	inittimer();
	while(1)
	{
		motor();
	}
}

 void timer_isr() interrupt 1
{
	TH0=(65536-value[count])/256; 
	TL0=(65536-value[count])%256;
	IN2=~IN2;	
	count++;
	if(count==2)
	{
		count=0;
	}
}