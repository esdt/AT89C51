#include"reg51.h"
sbit LED0=P2^0;
unsigned char a[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

void delay(unsigned int n)
{
	unsigned int i=0,j=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<120;j++);
	}
}

void led()
{	unsigned int i = 0;
	for(i=0;i<8;i++)
	{
		P1=(0x01<<i);
		P2=~(0x01<<i);//0000 0001  ->0000 0010 ->0000 0100
		delay(200);

	}

}

void led2()
{
	int i=0;
  	for(i=0;i<8;i++)
    {
   	  P2=~a[i];
	  delay(200);
    }
}
void led1()
{	unsigned int i = 0;
	for(i=0;i<8;i++)
	{
		P1=(0x01<<i);
		delay(200);

	}

}


void main()
{
	while(1)
	{				   
		led2();
	}
}