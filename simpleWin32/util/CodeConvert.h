#pragma once
typedef wchar_t WCHAR;
class CCodeConvert
{
public:
	CCodeConvert(void);
	~CCodeConvert(void);

	static void cpyMulti2Wide(char* pChar,WCHAR *pwChar);//խ�ֽڿ��������ֽ�
	static void cpyWide2Multi(WCHAR *pwChar,char* pChar);//���ֽڿ�����խ�ֽ�
	static void ConvertUnicode2Utf8(char*pSrc,char*pDes);//Unicode����ת��Ϊutf-8����
	static void ConvertUnicode2Gbk(char*pSrc,char*pDes);//Unicode����ת��Ϊgbk����
	static void ConvertAnsi2Unicode(char*pSrc,char*pDes);//ANSI����ת��ΪUnicode����
	static void ConvertAnsi2Utf8(char*pSrc,char*pDes);//ANSI����ת��Ϊutf-8����
	static void ConvertUtf82Unicode(char*pSrc,char*pDes);//utf-8����ת��ΪUnicode����
	static void ConvertUtf82Ansi(char*pSrc,char*pDes);//utf-8����ת��ΪANSI����
	static void ConvertUnicode2Ansi(char*pSrc,char*pDes);//Unicode����ת��ΪANSI����
};

