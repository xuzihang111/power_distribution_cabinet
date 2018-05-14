#ifndef __ERROR_H__
#define __ERROR_H__

#define uint unsigned int
#define uchar unsigned char 

sbit error_1 = P2^0;	//�쳣1  crc����
sbit error_2 = P2^1;	//�쳣2  ָ�����
sbit error_3 = P2^2;	//�쳣3	 ��������
sbit error_4 = P2^3;	//�쳣4

sbit stat_1 = P2^4;		//�ϵ�ָʾ
sbit stat_2 = P2^5;		//��������
sbit stat_3 = P2^6;		//����ָʾ
sbit stat_4 = P2^7;		//���Ա�־

sbit bell = P4^5;		//������
sbit key = P0^5;		//���Լ�

sbit relay_1 = P0^2;	//�̵���1
sbit relay_2 = P0^1;	//�̵���2
sbit relay_3 = P0^0;	//�̵���3

void Timer2Init(void);		//1����@24.000MHz
void speed(uint on, uint off, int num);

#endif