#pragma once
//异或测试
#include "stdafx.h"
#include "time.h"
#include "string"

using namespace std;

//删除string的空格
#ifndef TRIM
#define TRIM(p)  {if(!p.empty()){	p.erase(0, p.find_first_not_of(" \n\r\t")); \
	p.erase(p.find_last_not_of(" \n\r\t") + 1);}}
#endif

typedef struct
{
	unsigned char High;
	unsigned char Low;
}TypeHEXTOASCII;

class XorMechod{

public:
	//通过异或交换值
	static void XorExchange(int &a, int &b)
	{
		a = a^b;
		b = a^b;
		a = a^b;
	}

	//按字节异或测试
	static unsigned char XorEverybit(string strBits)
	{
		unsigned char cRet = 0;
		TRIM(strBits);

		int iSize =strBits.size();
		for (int i=0;i<iSize;i++)
		{
			cRet = cRet ^ strBits[i];
		}


		return cRet;
	}

	static unsigned int SumEveryBits(unsigned char bytes[],int num)
	{
		unsigned int iret = 0;
		for (int i=0;i<num;i++)
		{
			iret = iret + bytes[i];
		}

		return iret;
	}

	static bool CheckBCC(unsigned char cRxBuf[],int iRxLen)
	{
		int mI;
		unsigned char mBcc;
		int mN;
		mBcc=0;
		mN=(iRxLen-3);
		for(mI=0;mI<mN;mI++)
		{
			mBcc^=cRxBuf[mI];
		}
		TypeHEXTOASCII StructAsc = HexToAscII(mBcc);
		if(!(StructAsc.High==cRxBuf[iRxLen-3] && StructAsc.Low==cRxBuf[iRxLen-2]) )
			return false;
		return true;
	}

	//uch为16紧张0x0A 转换为字符串 两个字符'0' 'A'
	static TypeHEXTOASCII HexToAscII(unsigned char uch)
	{
		TypeHEXTOASCII StructAsc;

		StructAsc.High=((uch&0xF0)>>4);

		//数值转换为字符
		if(StructAsc.High>9)
			StructAsc.High = (StructAsc.High-10+'A');
		else
			StructAsc.High  =StructAsc.High+'0';

		StructAsc.Low=uch&0x0F;
		if(StructAsc.Low>9)
			StructAsc.Low = (StructAsc.Low-10+'A');
		else
			StructAsc.Low = StructAsc.Low+'0';

		return StructAsc;
	}
};

void testXorExchange()
{
	srand((unsigned)time(NULL));
	int maxValue = 100;
	int a = rand()%maxValue;
	int b = rand()%maxValue;
	printf("a=%d,b=%d\n",a,b);
	XorMechod::XorExchange(a,b);
	printf("After Exchange\n");
	printf("a=%d,b=%d\n",a,b);
}

void testXorEveryBit()
{
	unsigned char bytesTest[] = {0x01,0x0a,0x0b,0x02,0x08};
	int isize = (int)sizeof(bytesTest);
	string strBytes = string((char*)bytesTest,isize);
	unsigned char iret = XorMechod::XorEverybit(strBytes);
	printf("testXorEveryBit source:\n");
	for (int i=0;i<isize;i++)
	{
		printf("%02X ",strBytes[i]);
	}
	printf("\n");
	printf("result is %02X\n",iret);

	TypeHEXTOASCII StructAsc = XorMechod::HexToAscII(iret);
	printf("Hight = %c ",StructAsc.High);
	printf("LOW = %c\n",StructAsc.Low);

	getchar();
}


//测试
void testXorMechod()
{
	testXorEveryBit();

}