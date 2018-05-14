#include <STC15F2K60S2.H>
#include <ProtocolParsing.H>
#include <MODBUS.H>
#include <UART.H>
#include <intrins.h>
#include <ERROR.h>
#include <stdio.H>

TYPE_PACK dat_buf;		//解析信息的结构体
TYPE_MODBUS xdata modbus_struct_buf;

char xdata UART1_recv_buf[300];	//接收缓存
char xdata modbus_buf[255];
char xdata UART_send_buf[100];

uint UATR1_buf_count;				//接收缓存计数
bit UATR1_clear_flag = 1;			//接收缓存计数清除标志
bit UATR1_rece_flag;				//接收标志
bit UATR2_rece_flag;				//接收标志
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
		WDT_CONTR |= 0X10;	//喂狗
		stat_1 = 0;
		DataDarsing();
		
		if(!key)//测试 or 复位警报
		{	
			Send2String(MakeModbus(0x01,0x03,0x0017,6),8);//度ABC三项电压有效值	
			stat_4 = 0;
			while(!UATR2_rece_flag);	//等待数据返回
			stat_4 = 1;
			modbus_struct_buf = ModbusParsing(modbus_buf);
			
			value1 = calculate(modbus_struct_buf.dat);		//浮点型转换


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


void Uart1() interrupt 4						//串口1接收中断
{
	static uint UART1_rece_len;					//声明静态变量，用于存储应接收到的字节数
	if (RI)
	{
		stat_3 = 0;
		RI = 0;         						//清除S2RI位		
		if(SBUF == 0X7E && UATR1_clear_flag)	//判断到帧头，数据处理完后UATR1_clear_flag要置1
		{ 
			UATR1_buf_count = 0;				//清除计数标志
			UATR1_clear_flag = 0;				//清除计数标志清空标志
		}
		
		UART1_recv_buf[UATR1_buf_count] = SBUF;	//将接收到的字符存储
		
		if(UATR1_buf_count == 7)				//接收到了包长度数据
		{
			UART1_rece_len = UART1_recv_buf[6] << 8 | UART1_recv_buf[7];	//合成包长度数据
		}
		if(UATR1_buf_count == UART1_rece_len - 1)//本包数据接收完毕
		{
			UATR1_rece_flag = 1;				//对UART1_recv_buf处理完成后要将其清零
		}
		UATR1_buf_count++;		
		stat_3 = 1;		
	}
}	

void Uart2() interrupt 8
{
	static uchar UART2_recv_len;				//声明静态变量，用于存储应接收到的字节数
	
	if (S2CON & 0x01)
	{
		S2CON &= ~0x01;         				//清除S2RI位
		
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
		dat_buf = UnpackAgreement(UART1_recv_buf);	//解析数据包，将解析结果存到dat_buf中
		/*
		*以下为接收正常时的处理
		*/
		if(dat_buf.error == -1)
		{
			stat_2 = !stat_2;
			if(dat_buf.com == 0xff00)	//判断是否为查询指令
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
			else if(dat_buf.com == 0xff10)	//断电
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
				error_2 = 0;	//无有效指令
			}
		}
		/*
		*以下代码包含数据接收异常时的处理
		*/
		else							//如果接收到的数据包有误
		{
			if(dat_buf.error == CRC_ERROR)	//crc检验未通过
			{
				error_1 = 0;
			}
			else if(dat_buf.error == ADDRESS_ERROR)	//地址错误
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
	WDT_CONTR = 0x06;		//看门狗128分频
	WDT_CONTR |= 0X20;		//启动看门狗
	Uart1Init();			//115200bps@24.000MHz		通讯协议接收与发送
	Uart2Init();			//9600bps@24.000MHz		modbus协议收发	
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

















