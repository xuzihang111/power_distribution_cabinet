#ifndef __MODBUS_H__
#define __MODBUS_H__

#define uint unsigned int
#define uchar unsigned char 


typedef struct _TyteCRC{
	unsigned char High;
	unsigned char Low;
}TYPE_CRC;

typedef struct _TyteMODBUS{
	uchar len;
	uchar error;
	uchar *dat;
}TYPE_MODBUS;

char * MakeModbus(uchar addr, uchar com, int reg_addr, int len);
TYPE_MODBUS ModbusParsing(uchar *buf);
float calculate(char * buf);		//¸¡µãÐÍ×ª»»

#endif






























