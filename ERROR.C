#include <STC15F2K60S2.H>
#include <ERROR.H>

uint count = 0;
uint cycle,high_level;
int close = 0, close_count = 0;

void Timer2Init(void)		//1毫秒@24.000MHz
{
	AUXR |= 0x04;		//定时器时钟1T模式
	T2L = 0x40;			//设置定时初值
	T2H = 0xA2;			//设置定时初值
	AUXR |= 0x10;		//定时器2开始计时
}

void speed(uint on, uint off, int num)//
{
    IE2 |= 0x04;        //开定时器2中断
	cycle = on + off;
	high_level = on;
	close = num - 1;
}

void t2int() interrupt 12           //中断入口
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







