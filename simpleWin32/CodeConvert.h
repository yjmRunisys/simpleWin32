#pragma once
typedef wchar_t WCHAR;
class CCodeConvert
{
public:
	CCodeConvert(void);
	~CCodeConvert(void);

	static void cpyMulti2Wide(char* pChar,WCHAR *pwChar);//窄字节拷贝到宽字节
	static void cpyWide2Multi(WCHAR *pwChar,char* pChar);//宽字节拷贝到窄字节
	static void ConvertUnicode2Utf8(char*pSrc,char*pDes);//Unicode编码转化为utf-8编码
	static void ConvertUnicode2Gbk(char*pSrc,char*pDes);//Unicode编码转化为gbk编码
	static void ConvertAnsi2Unicode(char*pSrc,char*pDes);//ANSI编码转化为Unicode编码
	static void ConvertAnsi2Utf8(char*pSrc,char*pDes);//ANSI编码转化为utf-8编码
	static void ConvertUtf82Unicode(char*pSrc,char*pDes);//utf-8编码转化为Unicode编码
	static void ConvertUtf82Ansi(char*pSrc,char*pDes);//utf-8编码转化为ANSI编码
	static void ConvertUnicode2Ansi(char*pSrc,char*pDes);//Unicode编码转化为ANSI编码
};

