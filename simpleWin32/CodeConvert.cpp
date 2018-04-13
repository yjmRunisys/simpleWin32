#include "StdAfx.h"
#include "CodeConvert.h"
#include "windows.h"


CCodeConvert::CCodeConvert(void)
{
}


CCodeConvert::~CCodeConvert(void)
{
}

void CCodeConvert::cpyMulti2Wide(char* pChar,WCHAR *pwChar)
{
	int dwNum = MultiByteToWideChar (CP_ACP, 0,pChar,-1,NULL,0);
	MultiByteToWideChar(CP_ACP, 0,pChar,-1,pwChar,dwNum);
}

void CCodeConvert::cpyWide2Multi(WCHAR *pwChar,char* pChar)
{
	int dwNum = WideCharToMultiByte (CP_OEMCP, 0,pwChar,-1,NULL,0,NULL,FALSE);
	WideCharToMultiByte (CP_OEMCP, 0,pwChar,-1,pChar,dwNum,NULL,FALSE);
}

//ANSI编码转化为utf-8编码
void  CCodeConvert::ConvertAnsi2Utf8(char*pAnsi,char*pUtf8)
{
	char pUnicode[MAX_PATH];
	memset(pUnicode,0,MAX_PATH);
	ConvertAnsi2Unicode(pAnsi,pUnicode);
	ConvertUnicode2Utf8(pUnicode,pUtf8);

}


//Unicode编码转化为gbk编码
void CCodeConvert::ConvertUnicode2Gbk(char*pUnicode,char*pGbk)
{
	wchar_t *pwUnicode = (wchar_t*)pUnicode;
	int dwNum = WideCharToMultiByte (CP_ACP, 0,pwUnicode,-1,NULL,0,NULL,FALSE);
	WideCharToMultiByte (CP_ACP, 0,pwUnicode,-1,pGbk,dwNum,NULL,FALSE);

}

//Unicode编码转化为utf-8编码
void CCodeConvert::ConvertUnicode2Utf8(char*pUnicode,char*pUtf8)
{
	int len = WideCharToMultiByte(CP_UTF8,0,(const wchar_t*)pUnicode,-1,NULL,0,NULL,NULL);
	memset(pUtf8,0,len+1);
	WideCharToMultiByte(CP_UTF8,0,(const wchar_t*)pUnicode,-1,pUtf8,len,NULL,NULL);
}

//ANSI编码转化为Unicode编码
void CCodeConvert::ConvertAnsi2Unicode(char*pAnsi,char*pUnicode)
{
	wchar_t *pwUnicode = (wchar_t *)pUnicode;
	cpyMulti2Wide(pAnsi,pwUnicode);	
}

//utf-8编码转化为ANSI编码
void CCodeConvert::ConvertUtf82Ansi(char*pUtf8,char*pAnsi)
{
	char pUnicode[MAX_PATH];
	memset(pUnicode,0,MAX_PATH);
	ConvertUtf82Unicode(pUtf8,pUnicode);
	ConvertUnicode2Ansi(pUnicode,pAnsi);
}

//utf-8编码转化为Unicode编码
void CCodeConvert::ConvertUtf82Unicode(char*pUtf8,char*pUnicode)
{
	int len = MultiByteToWideChar(CP_UTF8,0,pUtf8,-1,NULL,0);
	memset(pUnicode,0,len+1);
	MultiByteToWideChar(CP_UTF8,0,pUtf8,-1,(wchar_t*)pUnicode,len);
}

//Unicode编码转化为ANSI编码
void CCodeConvert::ConvertUnicode2Ansi(char*pUnicode,char*pAnsi)
{
	wchar_t *pwUnicode = (wchar_t *)pUnicode;
	cpyWide2Multi(pwUnicode,pAnsi);	
}
