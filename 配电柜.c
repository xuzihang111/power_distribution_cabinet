#include <STC15F2K60S2.H>
#include <ProtocolParsing.H>
#include <MODBUS.H>
#include <UART.H>
#include <intrins.h>
TYPE_PACK dat_buf;			//������Ϣ�Ľṹ��
TYPE_MODBUS xdata modbus_struct_buf;

char xdata UART1_recv_buf[300];	//���ջ���
char xdata modbus_buf[255];
char *p;

uint UATR1_buf_count;				//���ջ������
bit UATR1_clear_flag = 1;			//���ջ�����������־
bit UATR1_rece_flag;				//���ձ�־
bit UATR2_rece_flag;				//���ձ�־
unsigned char xdata modbus_count = 0;

char UATR1_send_data[6] = {0x30,0x31,0x32,0x33,0x34,0x35};	//���ݰ��е����ݲ���

//unsigned char xdata modbus_time = 0;
//unsigned char xdata send_bud[50];
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


void main()
{
	Uart1Init();			//9600bps@24.000MHz
	Uart2Init();		//9600bps@24.000MHz
	EA = 1;
	while(1)
	{
		if(UATR1_rece_flag)
		{
			dat_buf = UnpackAgreement(UART1_recv_buf);	//�������ݰ�������������浽dat_buf��
			
			if(dat_buf.error == -1)
			{
							P60 = !P60;
				if(dat_buf.com == 0xff03)	//�ж��Ƿ�Ϊ��ѯָ��
				{
//					Send2String(dat_buf.dat,dat_buf.len - 10);
					P61 = !P61;
					Send2String(MakeModbus(0x01,0x03,0x0025,2),8);
					P66 = 0;
					while(!UATR2_rece_flag);
					P66 = 1;
					modbus_struct_buf = ModbusParsing(modbus_buf);
					Send1String(AgreementPackaging(ADDRESS,NUMBER,0xff03, modbus_struct_buf.len + 10 , 
													modbus_struct_buf.dat),modbus_struct_buf.len + 10);
					UATR2_rece_flag = 0;
					modbus_count = 0;
				
				}
								
			}
			else							//������յ������ݰ�����
			{
				P67 = !P67;;
				if(dat_buf.error == 2)		//������ַ���󣬽�����Ӧ�Ĵ����ɺ��ԣ���ͬ
				{
					P62 = 0;
					Delay1000ms();
					P62 = 1;
				}
				if(dat_buf.error == 3)	//������Ŵ���
				{
					P63 = 0;
					Delay1000ms();
					P63 = 1;
				}
				if(dat_buf.error == 4)	//���ݳ����쳣
				{
					P64 = 0;
					Delay1000ms();
					P64 = 1;
				}
				if(dat_buf.error == 6)	//crc����δͨ��
				{
					P65 = 0;
					Delay1000ms();
					P65 = 1;
				}
			}
			UATR1_clear_flag = 1;
			UATR1_rece_flag = 0;
		}
		
		
		
		if(!P73)
		{	
			Send2String(MakeModbus(0x01,0x03,0x0025,2),8);
			P66 = 0;
			while(!UATR2_rece_flag);
			P66 = 1;
			modbus_struct_buf = ModbusParsing(modbus_buf);
			Send1Data(modbus_struct_buf.len);
			Send1String(AgreementPackaging(ADDRESS,NUMBER,0xff03, modbus_struct_buf.len + 10, modbus_struct_buf.dat),modbus_struct_buf.len + 10);
			
			P67 = 0;
			while(!P73);
			P67 = 1;
			UATR2_rece_flag = 0;
			modbus_count = 0;
		}
	}
}


void Uart1() interrupt 4						//����1�����ж�
{
	static uint UART1_rece_len;					//������̬���������ڴ洢Ӧ���յ����ֽ���
	if (RI)
	{
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





























