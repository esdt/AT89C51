#include"reg51.h"
unsigned char a[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
unsigned char temp,temp1,temp2;
unsigned char num = 99;
void delay(unsigned int n)
{   
	unsigned int i,j;
   	for(i=0;i<n;i++)
   	{
   		for(j=0;j<120;j++);
   	} 
}
void keyscan()
{
	P1=0xf0;
	if(P1!=0xf0)//检测按键是否被按下
	{
		delay(20);
	 	temp1=P1;
		P1=0x0f;
		if(P1!=0x0f)
		{
			temp2=P1;
		}	
	}
	temp=temp1+temp2;
	if(temp==0xee)
	{
		num=0;	
	}
	if(temp==0xed)
	{
		num=1;	
	}
	if(temp==0xeb)
	{
		num=2;	
	}
	if(temp==0xe7)
	{
		num=3;	
	}
	if(temp==0xde)
	{
		num=4;	
	}
	if(temp==0xdd)
	{
		num=5;	
	}
	if(temp==0xdb)
	{
		num=6;	
	}
	if(temp==0xd7)
	{
		num=7;	
	}
	if(temp==0xbe)
	{
		num=8;	
	}
	if(temp==0xbd)
	{
		num=9;	
	}
}
void display()
{
	P2=a[num];
}
void main()
{	while(1)
	{	keyscan();
		display();
	}
}