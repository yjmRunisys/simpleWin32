#pragma once
#include "afxwin.h"
#include "atlbase.h"
#include "iostream"

#include "string"
using namespace std;
class XmlOperator
{
public:
	XmlOperator(void);
	~XmlOperator(void);

public:
	void ReadXmlOle(string xmlName);//��ȡxml
	string ReadXmlOneNode(CComPtr<IXMLDOMElement> &spRootEle,string section);//��ȡxmlĳ���ڵ�ֵ
	void WriteXmlOle(PVOID lpRoot,PVOID lpDoc,string xmlName);//дxml
	//�ڵ㴦����
	void ProcessNode(CComPtr<IXMLDOMNode>& spNode);

	string ConvertBstr2String(BSTR bstr);
	string ConvertBstr2String2(BSTR bstr);
	BSTR ConverString2Bstr(string str);
	BSTR ConverString2Bstr2(string str);
	BSTR ConverString2Bstr3(string str);
	BSTR ConvertCString2Bstr(CString cstr);
	CString ConvertBstr2CString(BSTR bstr);
	CComBSTR ConvertCString2Ccbstr(CString cstr);
	//CComBSTR Ϊ��BSTR�ķ�װ����ֱ��=��ֵ
};


//Sdk��ȡ
#import "msxml6.dll" 

class XmlSdk{
public:
	XmlSdk();
	~XmlSdk();

public:
	void ProcessNode(MSXML2::IXMLDOMNodePtr spNode);
	void ReadXml(string xmlName);//��ȡxml
};

void TestXml();


