#ifndef __ERROR_H__
#define __ERROR_H__

#define uint unsigned int
#define uchar unsigned char 

sbit error_1 = P2^0;	//异常1  crc错误
sbit error_2 = P2^1;	//异常2  指令不存在
sbit error_3 = P2^2;	//异常3	 其他错误
sbit error_4 = P2^3;	//异常4

sbit stat_1 = P2^4;		//上电指示
sbit stat_2 = P2^5;		//接收正常
sbit stat_3 = P2^6;		//接收指示
sbit stat_4 = P2^7;		//测试标志

sbit bell = P4^5;		//蜂鸣器
sbit key = P0^5;		//测试键

sbit relay_1 = P0^2;	//继电器1
sbit relay_2 = P0^1;	//继电器2
sbit relay_3 = P0^0;	//继电器3

void Timer2Init(void);		//1毫秒@24.000MHz
void speed(uint on, uint off, int num);

#endif
