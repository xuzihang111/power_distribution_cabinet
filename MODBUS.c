#include <MODBUS.H>
#include <STC15F2K60S2.H>
#include <math.H>


uchar code modbus_CRCH[]=  
{  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,  
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81,  
0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,  
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01,  
0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0,  
0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01,  
0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,  
0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81,  
0x40  
};  
  
uchar code modbus_CRCL[] =  
{  
0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,  
0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09,  
0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD,  
0x1D, 0x1C, 0xDC, 0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,  
0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7,  
0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A,  
0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38, 0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE,  
0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,  
0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2,  
0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4, 0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F,  
0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB,  
0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,  
0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0, 0x50, 0x90, 0x91,  
0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C,  
0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88,  
0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,  
0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,  
0x40  
};  

float code prescribing[] = {0.500000, 0.250000, 0.125000, 0.062500, 0.031250, 0.015625, 0.007813, 0.003906, 
							0.001953, 0.000977, 0.000488, 0.000244, 0.000122, 0.000061, 0.000031, 0.000015, 
							0.000008, 0.000004, 0.000002, 0.000001, 0.000000, 0.000000, 0.000000};

							
							
							
							
TYPE_CRC modbusCRC16(uchar *updata,uint len)  
{  
	TYPE_CRC DataCRC;
	uchar uchCRCHi=0xff;  
	uchar uchCRCLo=0xff;  
	uint  uindex;  
	while(len--)  
	{  
	  uindex = uchCRCHi ^ *updata++;  
	  uchCRCHi = uchCRCLo ^ modbus_CRCH[uindex];  
	  uchCRCLo = modbus_CRCL[uindex];  
	}  
    
	DataCRC.High = uchCRCHi;
	DataCRC.Low  = uchCRCLo;
	return DataCRC;  
}  

char * MakeModbus(uchar addr, uchar com, int reg_addr, int len)//合成modbus数据包
{
	char xdata return_buf[10];
	TYPE_CRC crc ;
	
	return_buf[0] = addr;
	return_buf[1] = com;
	return_buf[2] = reg_addr >> 8;
	return_buf[3] = reg_addr;
	return_buf[4] = len >> 8;
	return_buf[5] = len;
	
	crc = modbusCRC16(return_buf,6);
	
	
	return_buf[6] = crc.High;
	return_buf[7] = crc.Low;
	
	return return_buf;
}

TYPE_MODBUS ModbusParsing(uchar *buf)	//解析modbus数据包
{
	
	static uchar xdata out_put[150];
//	int i;
	int count = 0;
//	uchar len;
	TYPE_MODBUS modbus;
	TYPE_CRC crc;

	modbus.len = buf[2];
		
	for(count = 0;count <= modbus.len;count++)
		out_put[count] = 0;

	for(count = 0;count<modbus.len;count++)
	{
		out_put[count] = buf[count + 3];
	}
	modbus.dat = &out_put[0];
	
	crc = modbusCRC16(buf,modbus.len + 3);

	for(count = 0;count <= modbus.len;count++)
		buf[count] = 0;

	if((crc.High == buf[modbus.len + 4]) && (crc.Low == buf[modbus.len + 5]))
	{
		P62 = !P62;
		modbus.error = 0;
		return modbus;
	}
	else
	{
		modbus.error = 1;
		return modbus;
	}
}

float calculate(char * buf)		//浮点型转换
{
	char xdata i;
	unsigned char xdata S = 0, E = 0;
	float xdata M = 0.0;
	float xdata Val;
	
	S = buf[0] >> 7;
	E = (buf[0] << 1) | (buf[1] >> 7);
	E -= 127;
	
	for(i = 0;i < 8;i++)
	{
		if(buf[3] & 1)
		{
			M += prescribing[22 - i];
		}
		buf[3] >>= 1;
	}
	for(i = 0;i < 8;i++)
	{
		if(buf[2] & 1)
		{
			M += prescribing[14 - i];
		}
		buf[2] >>= 1;
	}
	for(i = 0;i < 7;i++)
	{
		if(buf[1] & 1)
		{
			M += prescribing[6 - i];
		}
		buf[1] >>= 1;
	}
	Val = (-1 * S) + pow(2, E) * (1 + M);
	
	return Val;
}














