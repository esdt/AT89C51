#include"reg51.h"
unsigned char a[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char count=0,num=0;

void inittimer()
{
	TMOD=0X01;
	TH0=(65536-50000)/256; //��ֵ�����ƶ�8λ
	TL0=(65536-50000)%256;//��ֵ�����ƶ�8λ		 50ms=50000us
	ET0=1; //��ʱ��/������T0������ж�����λ
	EA=1; //�ж������ܿ�λ
	TR0=1;	//������ʱ��
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
//�ⲿ�ж�0��interrupt 0 ,�жϱ�־λIE0��
//��ʱ��0��interrupt 1,�жϱ�־λTF0��
//�ⲿ�ж�1��interrupt 2 ,�жϱ�־λIE1��
//��ʱ��1��interrupt 3,�жϱ�־λTF1��
//�����жϣ�interrupt 4,�жϱ�־λRI\TI��
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