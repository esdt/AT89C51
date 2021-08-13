#include"reg51.h"
unsigned char a[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char count=0,num=0;

void inittimer()
{
	TMOD=0X01;
	TH0=(65536-50000)/256; //初值向右移动8位
	TL0=(65536-50000)%256;//初值向左移动8位		 50ms=50000us
	ET0=1; //定时器/计数器T0的溢出中断允许位
	EA=1; //中断允许总控位
	TR0=1;	//启动定时器
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
	inittimer();
	while(1)
	{
		display();
	}
}
//外部中断0，interrupt 0 ,中断标志位IE0；
//定时器0，interrupt 1,中断标志位TF0；
//外部中断1，interrupt 2 ,中断标志位IE1；
//定时器1，interrupt 3,中断标志位TF1；
//串口中断，interrupt 4,中断标志位RI\TI；
void timer_isr() interrupt 1
{
	TH0=(65536-50000)/256; 
	TL0=(65536-50000)%256;
	count++;
	if(count==20)
	{
		num++;
		count=0;
	}	

}