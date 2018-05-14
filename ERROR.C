#include <STC15F2K60S2.H>
#include <ERROR.H>

uint count = 0;
uint cycle,high_level;
int close = 0, close_count = 0;

void Timer2Init(void)		//1����@24.000MHz
{
	AUXR |= 0x04;		//��ʱ��ʱ��1Tģʽ
	T2L = 0x40;			//���ö�ʱ��ֵ
	T2H = 0xA2;			//���ö�ʱ��ֵ
	AUXR |= 0x10;		//��ʱ��2��ʼ��ʱ
}

void speed(uint on, uint off, int num)//
{
    IE2 |= 0x04;        //����ʱ��2�ж�
	cycle = on + off;
	high_level = on;
	close = num - 1;
}

void t2int() interrupt 12           //�ж����
{
	count++;
	if(count < high_level)
	{
		bell = 0;
	}
	else
	{
		bell = 1;
	}
	if(count > cycle)
	{
		count = 0;
		if(close <= close_count && close != -1)
		{
			IE2 &= ~0x04;
			close_count = 0;
			
		}
		else
		{
			close_count++;
		}
	}
}






