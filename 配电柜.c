#include <STC15F2K60S2.H>
#include <ProtocolParsing.H>
#include <MODBUS.H>
#include <UART.H>

TYPE_PACK dat_buf;			//������Ϣ�Ľṹ��

char xdata UART1_recv_buf[300];	//���ջ���
uint UATR1_buf_count;				//���ջ������
bit UATR1_clear_flag = 1;			//���ջ�����������־
bit UATR1_rece_flag;				//���ձ�־
//char UATR1_send_data[6] = {0xa4,0x34,0x88,0x27,0xb3,0x2e};	//���ݰ��е����ݲ���



void main()
{
	while(1)
	{
		
	}
}


void Uart1() interrupt 4				//����2�����ж�
{
	static uint rece_len;				//������̬���������ڴ洢ʵ�ʽ��յ����ֽ���
	if (RI)
	{
		RI = 0;         			//���S2RIλ
		if(SBUF == 0X7E && UATR1_clear_flag)	//�жϵ�֡ͷ
		{
			UATR1_buf_count = 0;				//���������־
			UATR1_clear_flag = 0;				//���������־��ձ�־
		}
		
		UART1_recv_buf[UATR1_buf_count] = SBUF;	//�����յ����ַ��洢
		
		if(UATR1_buf_count == 7)				//���յ��˰���������
		{
			rece_len = UART1_recv_buf[6] << 8 | UART1_recv_buf[7];	//�ϳɰ���������
		}
		if(UATR1_buf_count == rece_len - 1)	//�������ݽ������
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
		S2CON &= ~0x01;         //���S2RIλ
		modbus_buf[modbus_count] = S2BUF;
		modbus_count++;
	}
}

