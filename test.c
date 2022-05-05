#include <reg51.h>
#define uint unsigned int
#define uchar unsigned char
#define LED P0
#define CS P2
sbit S1=P3^0;
sbit S2=P3^1;
sbit S3=P3^2;
sbit S4=P3^3;
uchar key_s;
uchar LED_code[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
uchar dis_buff[2];
uint dat=99,count;
uint data_H,data_L;

void delay(uint ms)
{
	uint i;
	while(ms--)
	{
		for(i=0;i<125;i++);
	}
}

void key_scan(void)
{
	if(S1==0)
	{
		delay(100);
		if(S1==0)
			key_s=1;
	}
	else if(S2==0)
	{
		delay(100);
		if(S2==0)
			key_s=2;
	}
	else if(S3==0)
	{
		delay(100);
		if(S3==0)
			key_s=3;
	}
}
	
	void key_proc()
	{
		if(key_s==1)
		{TR0=1;}
		else if(key_s==2)
		{TR0=0;}
		else if(key_s==3)
		{
			TR0=0;
			dat=99;
		}
	}
void key_proc()
{
	if(S1==0)
	{
		delay(10);
		if(S1==0)
		{
			TR0=1;
			dat=99;
		}
	}
}
	
	void timer0() interrupt 1
	{
		count++;
		TH0=0x3C;
		TL0=0xB0;
		if(count>=20)
		{
			//bat--;
			count=0;
			if(dat>0)
				dat--;
			else
				dat=99;
		}
	}
	
	void data_timer(void)
	{
		if(count==20)
		{
			count=0;
			if(dat>0)
				dat--;
			else
				dat=99;
		}
	}
	
	void timer0_int(void)
	{
		TMOD=0x01;
		TH0=0x3C;
		TL0=0xB0;
		EA=1;
		ET0=1;
		TR0=0;
	}
	
	
	void data_int()
	{
		data_H=dat/10;
		data_L=dat%10;
		dis_buff[1]=data_H;
		dis_buff[0]=data_L;
	}
	
	void display()
	{
		CS=0x01;
		LED=LED_code[dis_buff[1]];
		delay(1);
		CS=0x02;
		LED=LED_code[dis_buff[0]];
		delay(1);
	}
	
	void display(uint x)
	{
		data_H=dat/10;
		data_L=dat%10;
		CS=0x01;
		LED=LED_code[data_H];
		delay(1);
		CS=0x02;
		LED=LED_code[data_L];
		delay(1);
	}
	
	
	void main(void)
	{
		timer0_int();
		while(1)
		{
			//key_scan();
			key_proc();
			//data_timer();
			//data_int();
			display(dat);
		}
	}
