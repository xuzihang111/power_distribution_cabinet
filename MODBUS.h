#ifndef __MODBUS_H__
#define __MODBUS_H__

#define uint unsigned int
#define uchar unsigned char 


typedef struct _TyteCRC{
	unsigned char High;
	unsigned char Low;
}TYPE_CRC;

char * MakeModbus(uchar addr, uchar com, int reg_addr, int len);
char * ModbusParsing(uchar *buf);


#endif






























