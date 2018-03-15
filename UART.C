#include <STC15F2K60S2.H>
#include <UART.H>


void UartInit(void)		//9600bps@24.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0x8F;		//设定定时初值
	TH1 = 0xFD;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	
}

void Uart2Init(void)		//9600bps@24.000MHz
{
	S2CON |= 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0x8F;			//设定定时初值
	T2H = 0xFD;			//设定定时初值
	AUXR |= 0x94;		//启动定时器2
	IE2 |= 0x01;
}

void Send1Data(char buf)//串口1发送单个字符
{
	SBUF = buf;
	while(!TI);
	TI = 0;
}

void Send1String(char *s,len)//串口1发送数组
{
	int i;
    for(i = 0; i < len;i++)      //检测字符串结束标志
    {
        Send1Data(*s++);         //发送当前字符
    }
}

void Uart2SendByte(char buf)//串口2发送单个字符
{
	S2BUF = buf;
	while(!(S2CON & 0x02));
	S2CON &= ~0x02;
	
}

void Send2String(char *s,len)//串口2发送数组
{
	int i;
    for(i = 0; i < len;i++)       //检测字符串结束标志
    {
        Uart2SendByte(*s++);      //发送当前字符
    }
}





















