#include"reg51.h"
//1001 1000 1100 0100 0110 0010 0011 0001
#define uchar unsigned char
#define uint unsigned int
uchar st[] = {0x90,0x08,0x0c,0x04,0x06,0x02,0x03,0x01};
uchar count=0,num=0,n=0;
//void delay(uint n)
//{   
//	uint i,j;
//   	for(i=0;i<n;i++)
//   	{
//   		for(j=0;j<120;j++);
//   	} 
//}

void inittimer()
{
	TMOD=0X01;
	TH0=(65536-50000)/256; //初值向右移动8位
	TL0=(65536-50000)%256;//初值向左移动8位		 50ms=50000us
	ET0=1; //定时器/计数器T0的溢出中断允许位
	EA=1; //中断允许总控位
	TR0=1;	//启动定时器
}

//void stepmotor()
//{
//	uint i=0;
//	for(i=7;i>0;i--)
//	{
//		P2=st[i];
//		delay(2500);
//
//	}
//		
//}
void main()
{
	inittimer();
	while(1)
	{
		//stepmotor();
	}
}

void timer_isr() interrupt 1
{
	TH0=0x3c; 
	TL0=0xB0;
	count++;
	if(count==20)
	{
		P2=st[num++];
		count=0;
		if(n==8)
		{
			n=0;
		}
	}
		

}