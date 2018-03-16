#ifndef __ProtocolParsing_H__
#define __ProtocolParsing_H__

#define uint unsigned int
#define uchar unsigned char 

/*������Ϣ��ʹ��ʱ�������Ҫ�����޸ı�����Ϣ*/

#define ADDRESS		0Xff60	//������ַ
#define NUMBER		0X00	//�������

/*��������*/
#define ERROR_NONE 			-1	//�޴���
#define FRAME_HARD_ERROR 	1 	//֡ͷ����
#define ADDRESS_ERROR		2	//������ַ����
#define NUMBER_ERROR		3	//������Ŵ���
#define LENGTH_OF_ERROR		4	//���ݳ����쳣
#define NO_DATA				5	//������
#define CRC_ERROR			6	//crc����δͨ��
/**/
//typedef struct _TyteCRC{		//crc�࣬����У��
//	unsigned char High;		
//	unsigned char Low;
//}TYPE_CRC;

typedef struct _TytePack{	//������Ϣ�Ľṹ��
	char error;				//��������
	uint addr;				//������ַ
	uchar num;				//�������
	uint com;				//ָ��
	uint len;				//���ݳ���
	uchar *dat;				//���ݣ����ݵ��׵�ַ������ݳ���ʹ��
}TYPE_PACK;


char * AgreementPackaging(uint addr ,uchar num ,uint com ,uint len ,uchar *buf);	//Э����
TYPE_PACK UnpackAgreement(char * buf);												//Э����

#endif




