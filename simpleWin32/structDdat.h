#pragma once
#include "stdafx.h"
#include "OutPut.h"
//���Խṹ�������ڴ�
struct STR_DATA{
	int sid;
	char* fileName;
};

void testStructData()
{
	STR_DATA mData;
	mData.sid = 1;
	mData.fileName = NULL;

	int iSize = sizeof(STR_DATA);//8
	char *pDataIni = (char*)&mData;//01 00 00 00 00 00 00 00 

	int nameLen = 8;
	mData.fileName = new char[nameLen];
	strcpy_s(mData.fileName,nameLen,"Good");
	pDataIni = (char *)&mData;//01 00 00 00 48 48 f3 02,���Ȳ��䣬�����ǵ�ַ��ʼ����


	int yjm = 1;
}