#include"reg51.h"
sbit RS=P3^0;
sbit RW=P3^1;
sbit E=P3^2;
unsigned char str[]={"0123456789"};
void delay(unsigned int n)
{  
	unsigned int i,j;
   for(i=0;i<n;i++)
   {
   		for(j=0;j<120;j++);
   } 
}
void writecom(unsigned char com)
{
	RS=0;
	RW=0;
	E=0;
	P2=com;
	delay(5);
	E=1;
	E=0;	
}
void writedat(unsigned char dat)
{
	RS=1;
	RW=0;
	E=0;
	P2=dat;
	delay(5);
	E=1;
	E=0;
}
void initlcd()
{
	writecom(0x38);
	writecom(0x0c);
	writecom(0x06);
	writecom(0x01);
}
void display()
{
	writecom(0x80);
//	writedat(str[0]);
//	delay(5);
	writedat(str[1]);
	delay(5);
	writedat(str[2]);
	delay(5);
	writedat(0XDF);
	delay(5);
	writedat(0x43);
	delay(5);		
}
void main()
{
	initlcd();
	while(1)
	{
		display();
	}
}