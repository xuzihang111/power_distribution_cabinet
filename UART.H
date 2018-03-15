#ifndef __UART_H__
#define __UART_H__

#define uint unsigned int
#define uchar unsigned char 

void UartInit(void);			//9600bps@24.000MHz
void Uart2Init(void);			//9600bps@24.000MHz
void Send1Data(char buf);		//串口1发送单个字符
void Send1String(char *s,len);	//串口1发送数组
void Uart2SendByte(char buf);	//串口2发送单个字符
void Send2String(char *s,len);	//串口2发送数组


#endif
