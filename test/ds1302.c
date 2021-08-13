#include"reg51.h"
#include"intrins.h"
#define uchar unsigned char
#define uint unsigned int
sbit RS=P3^0;
sbit RW=P3^1;
sbit E=P3^2;
sbit T_RST=P3^3;
sbit T_CLK=P3^4;
sbit T_IO=P3^5;
unsigned char str[]={"0123456789"};
uchar datechar[]={"DATA:"};
uchar timechar[]={"TIME:"};
uchar databuffer[10]={0x32,0x30,0,0,0x2d,0,0,0x2d,0,0};
uchar timebuffer[8]={0,0,0x3a,0,0,0x3a,0,0};
uchar weekbuffer={0x30};

void delay(unsigned int n)
{  
	unsigned int i,j;
   for(i=0;i<n;i++)
   {
   		for(j=0;j<120;j++);
   } 
}

uchar  ReadB(void) 
{ 
	uchar i,readdat=0;
	for(i=8; i>0; i--)
	{
		readdat=readdat>>1;
		if(T_IO)
		{
			readdat|=0x80;
		}
		T_CLK = 1;
		T_CLK = 0;            
	} 
	return(readdat); 
}

void  WriteB(uchar  dat)
{ 
   uchar  i;
   for(i=8; i>0; i--)
  {
        T_IO=dat&0x01;
        T_CLK = 1;
        T_CLK = 0;
        dat = dat >> 1; 
   } 
}

void  W1302(uchar address,uchar dat)
{
	T_RST = 0;
	T_CLK = 0;
	_nop_();
	_nop_();
	T_RST = 1;
	_nop_();
	_nop_();
	WriteB(address);         
	WriteB(dat);           
	T_CLK = 1;
	T_RST =0;
} 

uchar  R1302(uchar  address)
{
	uchar dat=0;
	T_RST = 0;
	T_CLK = 0;
	T_RST = 1;
	WriteB(address);           
	dat = ReadB();           
	T_CLK = 1;
	T_RST =0;
	return(dat);
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
	int i=0,temp=0;
	
	temp=R1302(0x8d);	 //����
	databuffer[2]=0x30+temp/16;
	databuffer[3]=0x30+temp%16;
	
	temp=R1302(0x8B);	  //����
	weekbuffer=0x30+temp;

	temp=R1302(0x89);	   //��
	databuffer[5]=0x30+temp/16;
	databuffer[6]=0x30+temp%16;
	
	temp=R1302(0x87);		//��
	databuffer[8]=0x30+temp/16;
	databuffer[9]=0x30+temp%16;
	
	temp=R1302(0x85);		 //Сʱ
	temp=temp&0x7f;
	timebuffer[0]=0x30+temp/16;
	timebuffer[1]=0x30+temp%16;	
	
	temp=R1302(0x83);		 //��
	timebuffer[3]=0x30+temp/16;
	timebuffer[4]=0x30+temp%16;
	
	temp=R1302(0x81);
	temp=temp&0x7f;		  //��
	timebuffer[6]=0x30+temp/16;
	timebuffer[7]=0x30+temp%16;
	
	writecom(0x80);		 
	for(i=0;i<5;i++)
	{
		writedat(datechar[i]);
	}
	writecom(0xc0);
	for(i=0;i<5;i++)
	{
		writedat(timechar[i]);
	}
	
	writecom(0x86);			 //��ʾ����
	for(i=0;i<10;i++)
	{
		writedat(databuffer[i]);
	}
	writecom(0xc6);			  //��ʾʱ��
	for(i=0;i<8;i++)
	{
		writedat(timebuffer[i]);
	}
	writedat(' ');
	writedat(weekbuffer);//��ʾ����		
}
void main()
{
	initlcd();
	W1302(0x8e,0);	   //��д����
	W1302(0x8c,0x21);  //д���꣬BCD��
	W1302(0x8A,0x01);  //д������
	W1302(0x88,0x08);  //д����
	W1302(0x86,0x09);  //д����
	W1302(0x84,0x12);  //д��Сʱ
	W1302(0x82,0x48);  //д���
	W1302(0x80,0x0
	0);  //д����
	W1302(0x8e,0x80);  //�ر�д����
	while(1)
	{
		display();
	}
}