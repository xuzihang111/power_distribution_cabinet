#include <STC15F2K60S2.H>
#include <ProtocolParsing.H>
#include <MODBUS.H>
#include <UART.H>
#include <intrins.h>
#include <ERROR.h>
#include <stdio.H>

TYPE_PACK dat_buf;		//������Ϣ�Ľṹ��
TYPE_MODBUS xdata modbus_struct_buf;

char xdata UART1_recv_buf[300];	//���ջ���
char xdata modbus_buf[255];
char xdata UART_send_buf[100];

uint UATR1_buf_count;				//���ջ������
bit UATR1_clear_flag = 1;			//���ջ�����������־
bit UATR1_rece_flag;				//���ձ�־
bit UATR2_rece_flag;				//���ձ�־
unsigned char xdata modbus_count = 0;

void Delay1000ms();
void DataDarsing(void);
void TheQuery(char addr,int reg,char len);
void ASK_ok();
void Init();


void main()
{
	float xdata value1, value2, value3;
	Init();
//	Send2String("hrllo",5);
	while(1)
	{
		WDT_CONTR |= 0X10;	//ι��
		stat_1 = 0;
		DataDarsing();
		
		if(!key)//���� or ��λ����
		{	
			Send2String(MakeModbus(0x01,0x03,0x0017,6),8);//��ABC�����ѹ��Чֵ	
			stat_4 = 0;
			while(!UATR2_rece_flag);	//�ȴ����ݷ���
			stat_4 = 1;
			modbus_struct_buf = ModbusParsing(modbus_buf);
			
			value1 = calculate(modbus_struct_buf.dat);		//������ת��


			sprintf(UART_send_buf,"Ua = %f",value1);
			Send1String(UART_send_buf,8);
			
//			Send1Data(0X00);
//			Send1Data(0X01);
//			Send1Data(0X17);
//			
//			
//			
//			Send1String(AgreementPackaging(ADDRESS,NUMBER,0xff03, modbus_struct_buf.len + 10, modbus_struct_buf.dat),modbus_struct_buf.len + 10);
			
			while(!key);
			UATR2_rece_flag = 0;
			modbus_count = 0;
			
			speed(200,0,1);
			error_4 = 1;
			error_3 = 1;
			error_2 = 1;
			error_1 = 1;
		}

	}
}


void Uart1() interrupt 4						//����1�����ж�
{
	static uint UART1_rece_len;					//������̬���������ڴ洢Ӧ���յ����ֽ���
	if (RI)
	{
		stat_3 = 0;
		RI = 0;         						//���S2RIλ		
		if(SBUF == 0X7E && UATR1_clear_flag)	//�жϵ�֡ͷ�����ݴ������UATR1_clear_flagҪ��1
		{ 
			UATR1_buf_count = 0;				//���������־
			UATR1_clear_flag = 0;				//���������־��ձ�־
		}
		
		UART1_recv_buf[UATR1_buf_count] = SBUF;	//�����յ����ַ��洢
		
		if(UATR1_buf_count == 7)				//���յ��˰���������
		{
			UART1_rece_len = UART1_recv_buf[6] << 8 | UART1_recv_buf[7];	//�ϳɰ���������
		}
		if(UATR1_buf_count == UART1_rece_len - 1)//�������ݽ������
		{
			UATR1_rece_flag = 1;				//��UART1_recv_buf������ɺ�Ҫ��������
		}
		UATR1_buf_count++;		
		stat_3 = 1;		
	}
}	

void Uart2() interrupt 8
{
	static uchar UART2_recv_len;				//������̬���������ڴ洢Ӧ���յ����ֽ���
	
	if (S2CON & 0x01)
	{
		S2CON &= ~0x01;         				//���S2RIλ
		
		modbus_buf[modbus_count] = S2BUF; 
		
		if(modbus_count == 2)
		{
			UART2_recv_len = modbus_buf[2];
		}
		
		if(modbus_count == UART2_recv_len + 4)
		{
			UATR2_rece_flag = 1;
		}
		
		modbus_count++;
	}
}


void Delay1000ms()		//@24.000MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 92;
	j = 50;
	k = 238;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void DataDarsing(void)
{
	if(UATR1_rece_flag)
	{
		dat_buf = UnpackAgreement(UART1_recv_buf);	//�������ݰ�������������浽dat_buf��
		/*
		*����Ϊ��������ʱ�Ĵ���
		*/
		if(dat_buf.error == -1)
		{
			stat_2 = !stat_2;
			if(dat_buf.com == 0xff00)	//�ж��Ƿ�Ϊ��ѯָ��
			{
				TheQuery(1,0x0017,6);
			}
			else if(dat_buf.com == 0xff01)
			{
				TheQuery(1,0x0023,4);
			}
			else if(dat_buf.com == 0xff02)
			{
				TheQuery(1,0x0029,4);
			}
			else if(dat_buf.com == 0xff03)
			{
				TheQuery(1,0x0031,4);
			}
			else if(dat_buf.com == 0xff04)
			{
				TheQuery(1,0x0039,4);
			}
			else if(dat_buf.com == 0xff05)
			{
				TheQuery(1,0x0041,4);
			}
			else if(dat_buf.com == 0xff06)
			{
				TheQuery(1,0x0049,3);
			}
			else if(dat_buf.com == 0xff10)	//�ϵ�
			{
				relay_1 = 0;
				ASK_ok();
			}
			else if(dat_buf.com == 0xff11)
			{
			
			}
			else if(dat_buf.com == 0xff12)
			{
			
			}
			else if(dat_buf.com == 0xff13)
			{
			
			}
			else if(dat_buf.com == 0xff14)
			{
			
			}
			else if(dat_buf.com == 0xff15)
			{
			
			}
			else if(dat_buf.com == 0xff16)
			{
			
			}
			else if(dat_buf.com == 0xff17)
			{
			
			}
			else if(dat_buf.com == 0xff18)
			{
				TheQuery(2,0x0017,6);
			}
			else if(dat_buf.com == 0xff19)
			{
				TheQuery(2,0x0023,4);
			}
			else if(dat_buf.com == 0xff1a)
			{
				TheQuery(2,0x0029,4);
			}
			else if(dat_buf.com == 0xff1b)
			{
				TheQuery(2,0x0031,4);
			}
			else if(dat_buf.com == 0xff1c)
			{
				TheQuery(2,0x0039,4);
			}
			else if(dat_buf.com == 0xff1d)
			{
				TheQuery(2,0x0041,4);
			}		
			else if(dat_buf.com == 0xff1e)
			{
				TheQuery(2,0x0049,3);
			}
			else 
			{
				error_2 = 0;	//����Чָ��
			}
		}
		/*
		*���´���������ݽ����쳣ʱ�Ĵ���
		*/
		else							//������յ������ݰ�����
		{
			if(dat_buf.error == CRC_ERROR)	//crc����δͨ��
			{
				error_1 = 0;
			}
			else if(dat_buf.error == ADDRESS_ERROR)	//��ַ����
			{
				error_4 = 0;
			}
			else
			{
				error_3 = 0;
			}
		}
		UATR1_clear_flag = 1;
		UATR1_rece_flag = 0;
	}
}


void TheQuery(char addr,int reg,char len)
{
	Send2String(MakeModbus(addr,0x03,reg,len),8);
	while(!UATR2_rece_flag);
	modbus_struct_buf = ModbusParsing(modbus_buf);
	Send1Data(0X00);
	Send1Data(0X01);
	Send1Data(0X17);
	Send1String(AgreementPackaging(ADDRESS,NUMBER,0xff03, modbus_struct_buf.len + 10 , 
									modbus_struct_buf.dat),modbus_struct_buf.len + 10);

	UATR2_rece_flag = 0;
	modbus_count = 0;
}

void ASK_ok()
{
	Send1Data(0X00);
	Send1Data(0X01);
	Send1Data(0X17);
	Send1String(AgreementPackaging(ADDRESS,NUMBER,0xff10, 12 , 
									"OK"),12);
}

void Init()
{
	P2M0 = 0XFF;
	P2M1 = 0X00;
	P0M0 = 0XFF;
	P0M1 = 0X00;
	P4M0 = 0XFF;
	P4M1 = 0X00;
	WDT_CONTR = 0x06;		//���Ź�128��Ƶ
	WDT_CONTR |= 0X20;		//�������Ź�
	Uart1Init();			//115200bps@24.000MHz		ͨѶЭ������뷢��
	Uart2Init();			//9600bps@24.000MHz		modbusЭ���շ�	
	Timer2Init();
	EA = 1;
	relay_1 = 1;
	stat_1 = 1;
	
	if(WDT_CONTR & 0x80)
	{
		error_4 = 0;
		WDT_CONTR &= ~0x80;
	}
	speed(200,0,1);
}

















