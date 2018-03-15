#ifndef __UART_H__
#define __UART_H__

#define uint unsigned int
#define uchar unsigned char 

void UartInit(void);			//9600bps@24.000MHz
void Uart2Init(void);			//9600bps@24.000MHz
void Send1Data(char buf);		//����1���͵����ַ�
void Send1String(char *s,len);	//����1��������
void Uart2SendByte(char buf);	//����2���͵����ַ�
void Send2String(char *s,len);	//����2��������


#endif