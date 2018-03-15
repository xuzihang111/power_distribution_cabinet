#include <STC15F2K60S2.H>
#include <UART.H>


void UartInit(void)		//9600bps@24.000MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0x8F;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	
}

void Uart2Init(void)		//9600bps@24.000MHz
{
	S2CON |= 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x04;		//��ʱ��2ʱ��ΪFosc,��1T
	T2L = 0x8F;			//�趨��ʱ��ֵ
	T2H = 0xFD;			//�趨��ʱ��ֵ
	AUXR |= 0x94;		//������ʱ��2
	IE2 |= 0x01;
}

void Send1Data(char buf)//����1���͵����ַ�
{
	SBUF = buf;
	while(!TI);
	TI = 0;
}

void Send1String(char *s,len)//����1��������
{
	int i;
    for(i = 0; i < len;i++)      //����ַ���������־
    {
        Send1Data(*s++);         //���͵�ǰ�ַ�
    }
}

void Uart2SendByte(char buf)//����2���͵����ַ�
{
	S2BUF = buf;
	while(!(S2CON & 0x02));
	S2CON &= ~0x02;
	
}

void Send2String(char *s,len)//����2��������
{
	int i;
    for(i = 0; i < len;i++)       //����ַ���������־
    {
        Uart2SendByte(*s++);      //���͵�ǰ�ַ�
    }
}




















