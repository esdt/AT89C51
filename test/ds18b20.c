#include"reg51.h"
sbit start=P3^0;
sbit RS=P3^0;
sbit RW=P3^1;
sbit E=P3^2;
sbit DQ=P3^3;
unsigned int readtemp = 0;
unsigned char str[]={"0123456789"};
unsigned char s[]={"Temperature:"};

void delay_18B20(unsigned int i)
{
	for(;i>0;i--);
}

void delay(unsigned int n)
{  
	unsigned int i,j;
   for(i=0;i<n;i++)
   {
   		for(j=0;j<120;j++);
   } 
}

void Init_DS18B20(void) 	  //��ʼ��
{
  unsigned char x=0;
  DQ = 1;          //DQ����
  delay_18B20(8);  //������ʱ
  DQ = 0;          //DQ����
  delay_18B20(80); //��ʱ����480us
  DQ = 1;          //��������
  delay_18B20(14);
  x=DQ;            //��x=0��ʼ���ɹ�����x=1��ʼ��ʧ��
  delay_18B20(20);
}

unsigned char ReadOneChar(void)	//��ʱ��
{
    unsigned char i=0;
    unsigned char dat = 0;
    for (i=8;i>0;i--)
    {
      DQ = 0; // ��������
      dat>>=1;//ÿ��ȡ��λ��������λ
      DQ = 1; //��������
      if(DQ)
      dat|=0x80;
      delay_18B20(4);
     }
     return(dat);
}

void WriteOneChar(unsigned char dat)//дʱ��
{
  unsigned char i=0;
  for (i=8; i>0; i--)
  {
   DQ = 0;
   DQ = dat&0x01;
   if(DQ){delay_18B20(1);DQ=1;}
	 else{delay_18B20(5);DQ = 1;}
   dat>>=1;
   }
}

unsigned char ReadTemperature(void)	 //���¶�
{							 
	 unsigned char a=0,b=0;
	 unsigned int temp=0;
	 Init_DS18B20();
	 WriteOneChar(0xCC);  // ���������кŲ���
	 WriteOneChar(0x44);  // �����¶�ת��
	 delay_18B20(100);    // 
	 Init_DS18B20();
	 WriteOneChar(0xCC);  //���������кŲ���
	 WriteOneChar(0xBE);  //��ȡ�¶ȼĴ���
	 delay_18B20(100);
	 a=ReadOneChar();     //���¶ȵ�λ
	 b=ReadOneChar();     //���¶ȸ�λ
	 temp=((b*256+a)>>4); //��ǰ�ɼ��¶ȳ�16�õ�ʵ���¶�
	 return(temp);
}

void writecom(unsigned char com)
{
	RS=0;
	RW=0;
	E=0;
	P1=com;
	delay(5);
	E=1;
	E=0;	
}
void writedat(unsigned char dat)
{
	RS=1;
	RW=0;
	E=0;
	P1=dat;
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
	unsigned char temp0=0,temp1=0,temp2=0;
	int i=0;
	temp0=readtemp/100;
	temp1=(readtemp%100)/10;
	temp2=readtemp%10;

	writecom(0x80);
	delay(5);
	while(s[i]!='\0')
	{
		writedat(s[i]);
		delay(5);
		i++;
	}
	writecom(0x80+0x40+5);
	writedat(str[temp0]);
	delay(5);
	writedat(str[temp1]);
	delay(5);
	writedat(str[temp2]);
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
		readtemp=ReadTemperature();
		display();	
	}
}