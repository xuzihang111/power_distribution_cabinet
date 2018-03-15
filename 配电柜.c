#include <STC15F2K60S2.H>
#include <ProtocolParsing.H>
#include <MODBUS.H>
#include <UART.H>

TYPE_PACK dat_buf;			//解析信息的结构体

char xdata UART1_recv_buf[300];	//接收缓存
uint UATR1_buf_count;				//接收缓存计数
bit UATR1_clear_flag = 1;			//接收缓存计数清除标志
bit UATR1_rece_flag;				//接收标志
//char UATR1_send_data[6] = {0xa4,0x34,0x88,0x27,0xb3,0x2e};	//数据包中的数据部分



void main()
{
	while(1)
	{
		
	}
}


void Uart1() interrupt 4				//串口2接收中断
{
	static uint rece_len;				//声明静态变量，用于存储实际接收到的字节数
	if (RI)
	{
		RI = 0;         			//清除S2RI位
		if(SBUF == 0X7E && UATR1_clear_flag)	//判断到帧头
		{
			UATR1_buf_count = 0;				//清除计数标志
			UATR1_clear_flag = 0;				//清除计数标志清空标志
		}
		
		UART1_recv_buf[UATR1_buf_count] = SBUF;	//将接收到的字符存储
		
		if(UATR1_buf_count == 7)				//接收到了包长度数据
		{
			rece_len = UART1_recv_buf[6] << 8 | UART1_recv_buf[7];	//合成包长度数据
		}
		if(UATR1_buf_count == rece_len - 1)	//本包数据接收完毕
		{
			UATR1_rece_flag = 1;
		}
		UATR1_buf_count++;			
		
	}
}

void Uart2() interrupt 8
{
	if (S2CON & 0x01)
	{
		S2CON &= ~0x01;         //清除S2RI位
		modbus_buf[modbus_count] = S2BUF;
		modbus_count++;
	}
}

