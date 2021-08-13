#include"reg51.h"
unsigned char a[]={0x3F,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
sbit key0= P1^0;
unsigned char num = 0;
void delay(unsigned int n)
{   
	unsigned int i,j;
   	for(i=0;i<n;i++)
   	{
   		for(j=0;j<120;j++);
   	} 
}
void seg()
{	P2=a[num];
	if(num==10)
	{
		num=0;
	}

}
void key()
{
	if(key0==0)
	{
		delay(200);
		if(key0==0)
		{
	 		num= num+1;

		}
	}
}
void main()
{	while(1)
	{	key();
		seg();
	}
}