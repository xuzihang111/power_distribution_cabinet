#ifndef __ProtocolParsing_H__
#define __ProtocolParsing_H__

#define uint unsigned int
#define uchar unsigned char 

/*本机信息，使用时请根据需要自行修改本机信息*/

#define ADDRESS		0Xff60	//本机地址
#define NUMBER		0X00	//本机编号

/*错误类型*/
#define ERROR_NONE 			-1	//无错误
#define FRAME_HARD_ERROR 	1 	//帧头错误
#define ADDRESS_ERROR		2	//本机地址错误
#define NUMBER_ERROR		3	//本机编号错误
#define LENGTH_OF_ERROR		4	//数据长度异常
#define NO_DATA				5	//无数据
#define CRC_ERROR			6	//crc检验未通过
/**/
//typedef struct _TyteCRC{		//crc类，用于校验
//	unsigned char High;		
//	unsigned char Low;
//}TYPE_CRC;

typedef struct _TytePack{	//解析信息的结构体
	char error;				//错误类型
	uint addr;				//本机地址
	uchar num;				//本机编号
	uint com;				//指令
	uint len;				//数据长度
	uchar *dat;				//数据，数据的首地址配合数据长度使用
}TYPE_PACK;


char * AgreementPackaging(uint addr ,uchar num ,uint com ,uint len ,uchar *buf);	//协议打包
TYPE_PACK UnpackAgreement(char * buf);												//协议解包

#endif




